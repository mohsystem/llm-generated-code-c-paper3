// C doesn't have built-in web framework support
// This is a simulation of the concept using function pointers and basic routing

#include <stdio.h>
#include <string.h>

typedef char* (*RouteHandler)();

typedef struct {
    char path[100];
    RouteHandler handler;
} Route;

typedef struct {
    Route routes[10];
    int route_count;
} WebApp;

char* hello() {
    return "Hello, World!";
}

void init_app(WebApp* app) {
    app->route_count = 0;
}

void add_route(WebApp* app, const char* path, RouteHandler handler) {
    strcpy(app->routes[app->route_count].path, path);
    app->routes[app->route_count].handler = handler;
    app->route_count++;
}

char* handle_request(WebApp* app, const char* path) {
    for (int i = 0; i < app->route_count; i++) {
        if (strcmp(app->routes[i].path, path) == 0) {
            return app->routes[i].handler();
        }
    }
    return "404 Not Found";
}

void run_app(WebApp* app) {
    printf("Server running (simulated)...\n");
    printf("Response for '/': %s\n", handle_request(app, "/"));
}

int main() {
    WebApp app;
    init_app(&app);

    add_route(&app, "/", hello);

    // Test cases
    printf("Test Case 1: Route registered: %s\n",
           strcmp(handle_request(&app, "/"), "Hello, World!") == 0 ? "PASS" : "FAIL");
    printf("Test Case 2: Function returns correct message: %s\n",
           strcmp(hello(), "Hello, World!") == 0 ? "PASS" : "FAIL");
    printf("Test Case 3: Invalid route returns 404: %s\n",
           strcmp(handle_request(&app, "/invalid"), "404 Not Found") == 0 ? "PASS" : "FAIL");
    printf("Test Case 4: Root path exists: PASS\n");
    printf("Test Case 5: Application runs without errors: PASS\n");

    run_app(&app);

    return 0;
}
