# Pac-Man Clone
### General Description
A clone of the popular pac-man game, with customized ghost behaviour.

Normal game state | Powered-up game state
:-------------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/45469027/112717056-6309a500-8eea-11eb-8bcf-a716efa09957.png) | ![image](https://user-images.githubusercontent.com/45469027/112717024-33f33380-8eea-11eb-9849-7b68d8a0a7f2.png)

### How does it work?
The game level construction is very similar to the construction of an unordered, weighted graph. Every possible turning point can be thought of as a vertex, while every path between the points is and edge. The weight of the edge is based on its length, that is, the longer the edge the higher the weight. A complete construction of this game's graph can be seen below:
![Pac-Man-Graph](https://user-images.githubusercontent.com/45469027/112724731-040d5580-8f15-11eb-8fc1-bae6364e7578.png)
