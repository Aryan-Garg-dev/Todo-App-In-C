# TODO Application with SQLite Database Integration

This project provides a command-line application written in C for managing TODO lists. It utilizes SQLite database for storing TODO items and user authentication.

## Features

- **User Authentication**: Users can authenticate themselves with a username and password.
- **TODO List Management**: Users can create, read, update, and delete TODO items.
- **SQLite Database Integration**: Utilizes SQLite for persistent storage of TODO items and user credentials.
- **Colorful Output**: Includes support for colored terminal output for a better user experience.

## Usage

Once the application is running, you can perform the following actions:

- **Authenticate User**: Users can authenticate themselves with their username and password.
- **Create TODO List**: Upon successful authentication, a TODO list is created for the user.
- **Add TODO Items**: Users can add new TODO items with a title, description, deadline, and completion status.
- **View TODO Items**: Users can view all TODO items in their list or filter by specific parameters.
- **Mark TODO Items as Complete**: Users can mark TODO items as complete.
- **Delete TODO Items**: Users can delete TODO items from their list.

## Dependencies

- **SQLite3**: This application relies on the SQLite database library for database operations.
