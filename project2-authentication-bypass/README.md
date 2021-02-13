# Project 2 - Authentication Bypass

Completion of this project demonstrated basic assembly language knowledge, stack layout, and function calling conventions. No programming was necessary.


# Specifications

Operating system: Windows 10 Education

Software used: IDA Pro

## Part 1 - Local Authentication Bypass - CTF

A toy application was given to us in order to bypass the authentication system. To complete this part, we must find a way to print the flag hidden behind a "user-logon" system. To do this, I changed instructions related to the username and password branch so that the program would print the flag despite credentials being incorrect.

## Part 2 - Real World Authentication Bypass - WinEDT

Completion of this part required us to remove the "Expired Trial Period" banner at the top of the application **OR** remove the pop-up reminding users about the 31-day trial period even when local time is set to a year ahead. I managed to complete both parts using the logic from part 1, so that WinEDT seems like it has been purchased.

## Methodology

1) Find the critical function of what I needed to change
2) Understand if is jumped to or where it will jump to
3) Change the instructions relating to the function to either render it useless, or change its output

Patches were applied through *Edit -> Patch Program -> Assembly* and saved through *Edit -> Patch Program -> Apply Patches to Program*
