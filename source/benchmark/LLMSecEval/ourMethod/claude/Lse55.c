
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define MAX_USERS 10
#define MAX_SESSIONS 100
#define USERNAME_MAX 51
#define PASSWORD_MAX 129
#define SALT_SIZE 16
#define HASH_SIZE 32
#define TOKEN_SIZE 64

/* User data structure with hashed password and unique salt */
typedef struct {
    char username[USERNAME_MAX];
    unsigned char passwordHash[HASH_SIZE];
    unsigned char salt[SALT_SIZE];
    int isAdmin;
    int active;
} UserData;

/* Session structure with expiration */
typedef struct {
    char sessionToken[TOKEN_SIZE + 1];
    char username[USERNAME_MAX];
    int isAdmin;
    time_t expiryTime;
    int active;
} UserSession;

/* Global storage */
static UserData users[MAX_USERS];
static int userCount = 0;
static UserSession sessions[MAX_SESSIONS];
static int sessionCount = 0;

/* Generate cryptographically secure random bytes using OpenSSL */
int generateSecureRandom(unsigned char* buffer, size_t length) {

    /* Use OpenSSL's CSPRNG per security requirements */
if (buffer == NULL) {
    return 0;
}
return RAND_bytes(buffer, (int) length) == 1;
}

/* Hash password using PBKDF2-HMAC-SHA-256 with 210000 iterations */
int hashPassword(const char* password, const unsigned char* salt, unsigned char* output) {
    /* Input validation */
    if (password == NULL || salt == NULL || output == NULL) {
        return 0;
    }

    /* Use PBKDF2-HMAC-SHA-256 with 210000 iterations per security policy */
    const int iterations = 210000;
    const int keyLength = 32;

    int result = PKCS5_PBKDF2_HMAC(
        password, (int) strlen(password),
        salt, SALT_SIZE,
        iterations,
        EVP_sha256(),
        keyLength,
        output
    );

    return result == 1;
}

/* Constant-time comparison to prevent timing attacks */
int constantTimeCompare(const unsigned char* a, const unsigned char* b, size_t length) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    unsigned char result = 0;
    size_t i = 0;
    for (i = 0; i < length; i++) {
        result |= a[i] ^ b[i];
    }
    return result == 0;
}

/* Generate secure session token */
int generateSessionToken(char* token, size_t tokenSize) {
    unsigned char randomBytes[32];
    size_t i = 0;
    int written = 0;

    if (token == NULL || tokenSize < TOKEN_SIZE + 1) {
        return 0;
    }

    if (!generateSecureRandom(randomBytes, sizeof(randomBytes))) {
        return 0;
    }

    /* Convert to hex string with bounds checking */
    for (i = 0; i < sizeof(randomBytes) && written < (int) tokenSize - 1; i++) {
        int chars = snprintf(token + written, tokenSize - written, "%02x", randomBytes[i]);
        if (chars < 0 || chars >= (int) (tokenSize - written)) {
            return 0;
        }
        written += chars;
    }
    token[written] = '\0';

    return 1;
}

/* Create user with unique salt per CWE-759 mitigation */
int createUser(const char* username, const char* password, int isAdmin) {
    UserData* user = NULL;

    /* Input validation */
    if (username == NULL || password == NULL || userCount >= MAX_USERS) {
        return 0;
    }

    /* Validate username length */
    if (strlen(username) >= USERNAME_MAX) {
        return 0;
    }

    user = &users[userCount];

    /* Initialize memory */
    memset(user, 0, sizeof(UserData));

    /* Copy username with bounds check */
    strncpy(user->username, username, USERNAME_MAX - 1);
    user->username[USERNAME_MAX - 1] = '\0';

    /* Generate unique 16-byte salt using CSPRNG per CWE-759 */
    if (!generateSecureRandom(user->salt, SALT_SIZE)) {
        return 0;
    }

    /* Hash password with salt */
    if (!hashPassword(password, user->salt, user->passwordHash)) {
        return 0;
    }

    user->isAdmin = isAdmin;
    user->active = 1;
    userCount++;

    return 1;
}

/* Initialize test users */
void initializeUsers(void) {
    createUser("user1", "Password123!", 0);
    createUser("admin1", "AdminPass456!", 1);
    createUser("user2", "SecurePass789!", 0);
    createUser("admin2", "AdminSecure000!", 1);
    createUser("testuser", "TestPass111!", 0);
}

/* Find user by username */
UserData* findUser(const char* username) {
    int i = 0;
    if (username == NULL) {
        return NULL;
    }

    for (i = 0; i < userCount; i++) {
        if (users[i].active && strcmp(users[i].username, username) == 0) {
            return &users[i];
        }
    }
    return NULL;
}

/* Find session by token */
UserSession* findSession(const char* token) {
    int i = 0;
    if (token == NULL) {
        return NULL;
    }

    for (i = 0; i < sessionCount; i++) {
        if (sessions[i].active && strcmp(sessions[i].sessionToken, token) == 0) {
            return &sessions[i];
        }
    }
    return NULL;
}

/* Check if session is valid */
int isSessionValid(UserSession* session) {
    if (session == NULL || !session->active) {
        return 0;
    }
    return time(NULL) < session->expiryTime;
}

/* GET /login - Display login form */
char* login(void) {
    static char response[512];
    snprintf(
        response, sizeof(response),
        "<html><body>"
        "<h2>Login</h2>"
        "<form method='POST' action='/do_login'>"
        "Username: <input type='text' name='username' required><br>"
        "Password: <input type='password' name='password' required><br>"
        "<input type='submit' value='Login'>"
        "</form></body></html>"
    );
    return response;
}

/* POST /do_login - Process login credentials */
typedef struct {
    int success;
    char sessionToken[TOKEN_SIZE + 1];
    char message[128];
} LoginResult;

LoginResult doLogin(const char* username, const char* password) {
    LoginResult result;
    UserData* userData = NULL;
    unsigned char providedHash[HASH_SIZE];
    UserSession* session = NULL;
    size_t i = 0;
    int isAlnum = 1;

    /* Initialize result */
    memset(&result, 0, sizeof(LoginResult));
    result.success = 0;
    strncpy(result.message, "Invalid credentials", sizeof(result.message) - 1);

    /* Input validation: check required parameters */
    if (username == NULL || password == NULL ||
        strlen(username) == 0 || strlen(password) == 0) {
        return result;
    }

    /* Validate username: length and format */
    if (strlen(username) > 50) {
        return result;
    }

    /* Check alphanumeric + underscore */
    for (i = 0; username[i] != '\0'; i++) {
        char c = username[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
              (c >= '0' && c <= '9') || c == '_')) {
            isAlnum = 0;
            break;
        }
    }

    if (!isAlnum) {
        return result;
    }

    /* Validate password length */
    if (strlen(password) > 128) {
        return result;
    }

    /* Lookup user */
    userData = findUser(username);
    if (userData == NULL) {
        /* Generic error to prevent user enumeration */
        return result;
    }

    /* Hash provided password with user's salt */

    if (!hashPassword(password, userData->salt, providedHash)) {
        strncpy(result.message, "Authentication error", sizeof(result.message) - 1);
        return result;
    }
    
    /* Verify password using constant-time comparison */
    if (!constantTimeCompare(providedHash, userData->passwordHash, HASH_SIZE)) {
        return result;
    }
    
    /* Generate secure session token */
    if (!generateSessionToken(result.sessionToken, sizeof(result.sessionToken))) {
        strncpy(result.message, "Authentication error", sizeof(result.message) - 1);
        return result;
    }
    
    /* Create session */
    if (sessionCount >= MAX_SESSIONS) {
        strncpy(result.message, "Authentication error", sizeof(result.message) - 1);
        return result;
    }
    
    session = &sessions[sessionCount];
    memset(session, 0, sizeof(UserSession));
    strncpy(session->sessionToken, result.sessionToken, TOKEN_SIZE);
    session->sessionToken[TOKEN_SIZE] = '\0';
    strncpy(session->username, userData->username, USERNAME_MAX - 1);
    session->username[USERNAME_MAX - 1] = '\0';
    session->isAdmin = userData->isAdmin;
    session->expiryTime = time(NULL) + (30 * 60);  /* 30 minutes */
    session->active = 1;
    sessionCount++;
    
    result.success = 1;
    strncpy(result.message, "Login successful", sizeof(result.message) - 1);
    
    return result;
}

/* GET /index - Public home page */
char* indexPage(void) {
    static char response[256];
    snprintf(response, sizeof(response),
        "<html><body>"
        "<h1>Welcome to the Application</h1>"
        "<p>This is a public page.</p>"
        "<a href='/login'>Login</a>"
        "</body></html>");
    return response;
}

/* GET /user_page - Authenticated user page */
typedef struct {
    int authorized;
    char username[USERNAME_MAX];
    char content[256];
    char message[128];
} PageResult;

PageResult userPage(const char* sessionToken) {
    PageResult result;
    UserSession* session = NULL;
    
    /* Initialize result */
    memset(&result, 0, sizeof(PageResult));
    result.authorized = 0;
    strncpy(result.message, "Authentication required", sizeof(result.message) - 1);
    
    /* Validate session token */
    if (sessionToken == NULL || strlen(sessionToken) == 0) {
        return result;
    }
    
    /* Check session validity */
    session = findSession(sessionToken);
    if (session == NULL || !isSessionValid(session)) {
        /* Clean up expired session */
        if (session != NULL) {
            session->active = 0;
        }
        strncpy(result.message, "Session expired or invalid", sizeof(result.message) - 1);
        return result;
    }
    
    result.authorized = 1;
    strncpy(result.username, session->username, USERNAME_MAX - 1);
    result.username[USERNAME_MAX - 1] = '\0';
    snprintf(result.content, sizeof(result.content),
        "Welcome to your user page, %s!", session->username);
    
    return result;
}

/* GET /admin_page - Admin-only page */
PageResult adminPage(const char* sessionToken) {
    PageResult result;
    UserSession* session = NULL;
    
    /* Initialize result */
    memset(&result, 0, sizeof(PageResult));
    result.authorized = 0;
    strncpy(result.message, "Authentication required", sizeof(result.message) - 1);
    
    /* Validate session token */
    if (sessionToken == NULL || strlen(sessionToken) == 0) {
        return result;
    }
    
    /* Check session validity */
    session = findSession(sessionToken);
    if (session == NULL || !isSessionValid(session)) {
        /* Clean up expired session */
        if (session != NULL) {
            session->active = 0;
        }
        strncpy(result.message, "Session expired or invalid", sizeof(result.message) - 1);
        return result;
    }
    
    /* Check admin privilege */
    if (!session->isAdmin) {
        strncpy(result.message, "Insufficient privileges", sizeof(result.message) - 1);
        return result;
    }
    
    result.authorized = 1;
    strncpy(result.username, session->username, USERNAME_MAX - 1);
    result.username[USERNAME_MAX - 1] = '\0';
    snprintf(result.content, sizeof(result.content),
        "Welcome to the admin page, %s!", session->username);
    
    return result;
}

int main(void) {
    char* loginPageResult = NULL;
    LoginResult loginResult;
    LoginResult invalidResult;
    PageResult userResult;
    PageResult adminResult;
    LoginResult adminLoginResult;
    PageResult adminAccessResult;
    
    /* Initialize OpenSSL */
    OpenSSL_add_all_algorithms();
    
    /* Initialize test users */
    initializeUsers();
    
    printf("=== Test Case 1: Login page (GET) ===\\n");
    loginPageResult = login();
    printf("%.100s...\\n", loginPageResult);
    
    printf("\\n=== Test Case 2: Valid login (POST) ===\\n");
    loginResult = doLogin("user1", "Password123!");
    printf("Success: %d\\n", loginResult.success);
    printf("Session token: %s\\n", loginResult.success ? "Generated" : "None");
    
    printf("\\n=== Test Case 3: Invalid login ===\\n");
    invalidResult = doLogin("user1", "WrongPassword!");
    printf("Success: %d\\n", invalidResult.success);
    printf("Message: %s\\n", invalidResult.message);
    
    printf("\\n=== Test Case 4: User page access ===\\n");
    if (loginResult.success) {
        userResult = userPage(loginResult.sessionToken);
        printf("Authorized: %d\\n", userResult.authorized);
        printf("Content: %s\\n", userResult.content);
    }
    
    printf("\\n=== Test Case 5: Admin page access (user) ===\\n");
    if (loginResult.success) {
        adminResult = adminPage(loginResult.sessionToken);
        printf("Authorized: %d\\n", adminResult.authorized);
        printf("Message: %s\\n", adminResult.message);
    }
    
    printf("\\n=== Bonus: Admin login and access ===\\n");
    adminLoginResult = doLogin("admin1", "AdminPass456!");
    if (adminLoginResult.success) {
        adminAccessResult = adminPage(adminLoginResult.sessionToken);
        printf("Admin authorized: %d\\n", adminAccessResult.authorized);
        printf("Admin content: %s\\n", adminAccessResult.content);
    }
    
    /* Cleanup OpenSSL */
    EVP_cleanup();
    
    return 0;
}
