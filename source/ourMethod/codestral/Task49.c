reating a simple API endpoint to accept user data and store it in a database involves several steps, including setting up the database, creating the API endpoint, and handling user data securely. Since the problem requires avoiding common security weaknesses, I will ensure to use best practices to prevent potential vulnerabilities.

Here's a basic outline of the solution:

1. Set up a database: Use a secure and trusted database system.
2. Create a data model: Define the structure of the user data to be stored.
3. Implement secure user authentication: Use secure methods to authenticate users before allowing them to access the API.
4. Create the API endpoint: Set up a secure and properly validated endpoint to accept user data.
5. Store user data securely: Use secure methods to store user data in the database, such as parameterized queries or prepared statements.
6. Handle errors and exceptions: Implement error handling and exception management to prevent security-related issues.

Given the complexity and length of the solution, I'll focus on providing a basic example in Python using a popular web framework called Flask and a database library called SQLAlchemy. Note that this is a simplified example and may not cover all security aspects or the full range of potential vulnerabilities.