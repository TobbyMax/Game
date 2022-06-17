# SFML Ping Pong

## Description
* Simple Ping Pong project as an assignment from HSE Programming course.
* Multiplayer game, where people connect to the server and play Ping Pong till 3 points.
* There is a simple physics for ball, paddles and also physics of richochet.

We used [SFML](https://www.sfml-dev.org/index.php) library because it is a very efficient tool, which is simple in learning and application.

We faced numerous challenges during the devising of the game, such as issues with the connection and drawing, but have successfully passed them!

We still have a desire to clean the code and make it more readable, but now we don't have sufficient amount of time to cope with it because of exams in university 😞.

## Table of Contents (i think it's optional)

## Dependencies
```IDE (CLion is preffered)```

```Stable and fast internet connection```

```Good mood and a desire to win!```

> SFML library is not required, it is already installed in the project (even twice!).

> CMakeList.txt links everything greatly so you don't have to care about it.

## How to Install and Run the Project
1. Clone this repository on your computer.
2. Create a local network with your friends and connect to it (use, for instance, [Hamachi](https://www.vpn.net/)).
   
   ![image](https://user-images.githubusercontent.com/46136468/174265344-c766426a-48ac-42a4-a808-b940cc94593e.png)
   
3. Use CLion (preffered) or other instrument to open the project.
4. If you want to open the server, just select folder ```GameServer``` and CLion will help you build it.
  
   ![image](https://user-images.githubusercontent.com/46136468/174266718-7c257aba-2f24-4661-b721-d665ccc6aaec.png)

5. If you want to be a player, you should open ```GameClient``` folder and set in ```Game.h``` server IP, which you can obtain from Hamachi.

   ![image](https://user-images.githubusercontent.com/46136468/174267759-dac8ecbb-53c8-4833-8ea8-4bd5e00b541f.png)

6. Start the server code.
7. Both players connect to the server.
8. Game starts, when both players are connected.
9. Enjoy the game!

   ![image](https://user-images.githubusercontent.com/46136468/174269275-a61fbacc-78b6-4b6f-9324-14d591ba8caa.png)


10. Game will be ended, when some player will close the game window or lose the connection with a server.

## Credits
[Pasha Medvedev](https://t.me/nightshift48)

[Maksim Ageev](https://t.me/maxveega)

## License
MIT License (will be added later)
