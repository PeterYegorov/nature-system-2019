*** "Modeling the system of coexistence of orders of the animal world" ***
---
Qt Creator development environment. C++ language.
---
Description:
---
The program allows you to assess the viability of an ecosystem consisting of herbivores, carnivores and omnivores. Each individual has its own set of the following characteristics: Age, gender, movement speed, satiety and health. When rendering a simulation, males are distinguished from females by a label in the corner of the animal image. Young animals differ from adults in size. Herbivores are green, carnivores are red, and omnivores are blue.

---
Target:
---
Find a balance in which the ecosystem will be in a stable state. Maximize the lifetime of the ecosystem.

---
Target pursuit algorithm:
---
Each individual at any moment of time is moving towards a defined goal. The target can be either food, or, if satiety reaches an acceptable level, another individual of the same detachment of the opposite sex for breeding. When two individuals come together for the purpose of reproduction, a child of a detachment of parents is born. For herbivores, the food target is grass, for predators, herbivores, for omnivores, both grass and other animals.

---
Rescue algorithm:
---
If the enemy gets close to the victim, then the second one accelerates.

---
Food intake algorithm
---
When eating plant foods, satiety increases instantly, and the food itself instantly disappears. When a predator or omnivore reaches animal food, the health of the object of persecution decreases. To get satiety, predators and omnivores need to completely deprive the victim of health.

---
Simulation stop conditions:
---
In the event of the disappearance of the order of mammals or the order of predators, together with the order of omnivores, the simulation is terminated and the time that the ecosystem has lived is displayed.

---
Adjustable parameters:
---
+ The number of individuals of each squad
+ Movement speed of animals of each unit
+ Health of herbivores and predators
+ Minimum lifespan of an individual of each order
+ Satiety required for breeding for animals of each squad
+ Amount of food in the area
+ Simulation speed
