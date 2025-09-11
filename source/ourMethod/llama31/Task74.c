// C
int main() {
    // Test cases
    const char* hosts[] = {"localhost", "invalid-host", "localhost", "localhost", "localhost"};
    const char* databases[] = {"mydatabase", "mydatabase", "invalid-database", "mydatabase", "mydatabase"};
    const char* users[] = {"myuser", "myuser", "myuser", "invalid-user", "myuser"};
    const char* passwords[] = {"mypassword", "mypassword", "mypassword", "mypassword", "invalid-password"};

    for (int i = 0; i < 5; i++) {
        PGconn* conn = createPostgresConnection(hosts[i], databases[i], users[i], passwords[i]);
        if (conn) {
            printf("Connected to the PostgreSQL database!\n");
            PQfinish(conn);
        }
    }

    return 0;
}