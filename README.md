# SimpleUserLoginAndRegistration
A simple C project to provide the user either Log-in or Register in a certain limitations.

Requirements:

Username:
    • Can only have [a-z], [A-Z] and [0-9] characters.
    • Minimum length: 5
    • Maximum length: 30
    • Must have at least  1 Upper Character, 1 Lower Character and 1 Number.

Mail Adress:
    • Can only have [a-z], [A-Z], [0-9] and [@._-] characters.
    • Can only start with [a-z], [A-Z] and [0-9]  characters.
    • Minimum length is 5
    • Maximum length: 40

Password:
    • Can have any character.
    • Minimum length is 10
    • Maximum length: 30
    • Password must have at leat 1 Upper Character, 1 Lower Character, 1 Number and 1 Special Character


Login page:
    • Enter a username.
    • Enter a password.
    • If password and username matches, You will log in.
    • If username is correct but password is wrong, You can’t log in. And account locker will increase. IF you try to enter a wrong password to a specific username for 3 times, account will be locked.

Register:
    • Enter a username.
    • If username is already taken or username not valid, try again.
    • Enter a mail.
    • If mail is already taken or mail is not valid, try again.
    • Enter a password.
    • If password is not valid, try again.
    • If everything is correct, register and go to the main menu.
