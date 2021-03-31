<div align="center">
  <img width="600" height="200" src="https://external-content.duckduckgo.com/iu/?u=http%3A%2F%2Fimg.huffingtonpost.com%2Fasset%2Fscalefit_720_noupscale%2F58f9108d2600001b00c46cfe.jpg&f=1&nofb=1" alt="Ghost in the Shell">
</div>

> It is the year 2029. Technology has advanced so far that cyborgs are commonplace.
> In addition, human brains can connect to the internet directly. Major Motoko Kusanagi
> is an officer in Section 9, an elite, secretive police division that deals with special
> operations, including counter terrorism and cyber crime. She is currently on the trail
> of the Puppet Master, a cyber criminal who hacks into the brains of cyborgs in order to
> obtain information and to commit other crimes

# Brief

<img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fimage.tmdb.org%2Ft%2Fp%2Foriginal%2Fv5NNSikH5w7Bz8SDcqxLEwVD4wW.jpg&f=1&nofb=1" style="width:200px; float:right;" alt=""/>

For this final and third game in your portfolio, in groups of four, you will
need to create a tangentially linked game, with local multi-player support based
on the themes and ideas explored in the legendary Manga movie Ghost in the Shell.
The multi-player support, can either be PVP or COOP but must be present and the
framework used for this game will be ASGE.

You are free to choose the theme, its genre, as well as the storyline for
your game, but it should not be a direct clone of the movie, rather you should
explore one of more the themes present within it.

Your group will need to present your game idea in an online session in order
to get it greenlit and to field questions and answers about your games' design.

*The module team will be responsible for greenlighting the game's development.*

Weighting
------
This game forms 50% of your final portfolio grade

Project Layout
------
* app
  * ASGEGame: the game client and OpenGL Window
    * data: used for assets and game deployment
    * resources: used for icons 
  
* extern
  * important build scripts and other submodules
  * to update the submodules manually
    * `git pull --recurse-submodules`
    * `git submodule update --init --remote --recursive`
  
* include:
  * ASGEGameLib: header files belonging to your game 
* src 
  * **reusable game components go here i.e. dice, animated sprite, game panel, game state  etc** 
  * The corresponding hpp files go in the include directory
   
   
Static Analysis
------
CLion will automatically apply clang-tidy settings to your project.
Just make sure to resolve any warnings it flags to prevent the CI checks
from failing. Cppcheck support has also been enabled if you've installed
it locally on the machine and a Cppcheck build target will be shown if the
exe was located. You can ignore any errors relating to third-party libraries. 

GameData
------
In order to access your game data from the game, you need to ensure that the +GD target has been run. You need to run this when you've modified the contents of your Data folder. 
