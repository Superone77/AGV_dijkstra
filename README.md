
### 基于dijkstra算法的AGV路径规划 AGV path planning based on dijkstra algorithm

#### dijkstra算法 dijkstra algorithm

经典Dijkstra算法是一种贪心算法，根据路径长度递增次序找到最短路径，通常用于解决单源最短路的问题。Dijkstra算法的基本思想是：首先根据原有路径图，初始化源点到与其相邻节点的距离，选出与源点最短距离的节点进行松弛操作，即比较判断若经过该点，是否能找到比源点到其他点更短的距离，若有更短的距离则更新原有距离，直至遍历初始图中的所有节点。Dijkstra算法可找出源点到初始图中所有点的最短距离，任意最短路径的子路径仍为最短路径。
     
Dijkstra算法是以标号为基础的标签算法，设一个有向图由n个点和e条弧组成，该有向图可表示为G=(V,E)，V表示节点集，E表示弧集，可用C(A,B)来表示A和B点之间弧的长度，若在该有向图中A点和B点间不可达，则可用无穷大或者远大于C(A,B)数量级的整数来表示。可设一个数组DIST(X)来表示节点X与原点v0之间的距离，S和V-S分别表示目前暂确定找到最短路径节点的集合与未确定最短路径节点集合，初始时S仅包含v0源点，算法结束时S应包含所有节点。

Dijkstra算法的步骤如下：
**Step.1** 初始化，将源点v0加入集合S，并做标记；
**Step.2** 在V-S中寻找与v0有连接的点，并选择距离最短的点i做标记，将其加入S中；
**Step.3** 将i作为新的起始点，在V-S中寻找与i直接可达且距离最短的点j，若DIST[j]>DIST[i]+C(i,j)，意味着目前来看从源点到j的距离经过i点比直接从v0到j要短，所以将DIST[j]更新为DIST[i]+C(i,j)，并将j点加入S集合；
**Step.4** 重复Step.2、Step.3步骤n-1次，可找到源点v0到所有点的最短距离；
**Step.5** 依次输出源点、中间点、目标点连成路径。

The classic Dijkstra algorithm is a greedy algorithm that finds the shortest path according to the ascending order of path length. It is usually used to solve the single-source shortest path problem. The basic idea of ​​the Dijkstra algorithm is: first, according to the original path graph, initialize the distance from the source point to its adjacent nodes, select the node with the shortest distance to the source point for relaxation operation, that is, compare and judge whether a shorter distance can be found than the distance from the source point to other points if passing through this point. If there is a shorter distance, update the original distance until all nodes in the initial graph are traversed. The Dijkstra algorithm can find the shortest distance from the source point to all points in the initial graph, and the subpath of any shortest path is still the shortest path.
Dijkstra algorithm is a labeling algorithm based on labeling. Suppose a directed graph consists of n points and e arcs. The directed graph can be represented as G=(V,E), where V represents the node set and E represents the arc set. C(A,B) can be used to represent the length of the arc between points A and B. If points A and B are unreachable in the directed graph, they can be represented by an integer of infinity or much larger than C(A,B). An array DIST(X) can be set to represent the distance between node X and the origin v0. S and V-S represent the set of nodes that have been temporarily determined to find the shortest path and the set of nodes that have not been determined to find the shortest path. Initially, S only contains the source point v0. When the algorithm ends, S should contain all nodes.

The steps of Dijkstra algorithm are as follows:
**Step.1** Initialize, add source point v0 to set S and mark it;
**Step.2** Find points connected to v0 in V-S, select point i with the shortest distance to mark it, and add it to S;
**Step.3** Take i as the new starting point, find point j in V-S that is directly reachable from i and has the shortest distance. If DIST[j]>DIST[i]+C(i,j), it means that the distance from the source point to j through point i is shorter than that from v0 to j directly, so update DIST[j] to DIST[i]+C(i,j), and add point j to set S;
**Step.4** Repeat Step.2 and Step.3 n-1 times to find the shortest distance from source point v0 to all points;
**Step.5** Output the source point, intermediate point, and target point in sequence to form a path.

#### 项目背景 Project Background

现代化仓库中AGV（自动避障小车）的使用颇多，本项目为AGV的路径规划和多车避让提供一种较为初级的解决方案。

首先，基于实际仓库运作场景，本文做出以下假设：
* 通常情况下，AGV的数量恒定，不考虑AGV突然增加或减少的情况；
* AGV运行速度恒定，不考虑停下加速或减速停下的时段，且空载和负载状态下AGV运行速度相等；
* 订单是否优先级由上位机确定，分配给AGV执行；
* 每台AGV一次只能执行一个任务，且一个任务能且仅能被一台AGV执行一次；
* 本文设定AGV系统采用集中式控制方式，各AGV的任务来源于上位机，且每台AGV均与上位机通信，AGV之间没有信息交互。

根据作业类型，AGV系统可由三个模块组成：任务生成模块、任务分配模块和路径规划模块。仓库不断接收到新订单，则任务生成模块不断生成新任务，不断进行着任务分配和路径规划。AGV系统的整体作业流程如下：


1. **任务生成**：上位机接收仓库订单，将其转化为AGV可执行的任务，生成一个任务集合，任务完成后则从任务集合中删除该任务。
2. **任务分配**：此模板的目标是确保每个任务圆满完成的情况下总的任务完成最短。在一定的任务序列优化规则下，结合任务的优先级，给AGV传达任务指令。另外，任务分配还需要考虑各个AGV的均衡运作，避免部分AGV由于任务过于繁重而降低寿命。由于AGV的运行是时间连续性的，所以任务分配模块给AGV传达的是一个任务序列，AGV按照此序列依次执行任务。
3. **路径规划**：在实际情况中，一个仓库往往有多台AGV，路径规划模块最重要的是为每一台AGV合理规划路径，当AGV接收到特定任务时，首先需要为其初步规划行走路线，根据其他AGV的行走状况进行必要的调整，避免出现碰撞或死锁情况。

AGV (Automatic Obstacle Avoidance Vehicle) is widely used in modern warehouses. This project provides a relatively basic solution for AGV path planning and multi-vehicle avoidance.

First, based on the actual warehouse operation scenario, this article makes the following assumptions:
* Under normal circumstances, the number of AGVs is constant, and the sudden increase or decrease of AGVs is not considered;
* The running speed of AGV is constant, and the period of stopping to accelerate or decelerate is not considered, and the running speed of AGV is equal under no-load and load conditions;
* The priority of the order is determined by the host computer and assigned to the AGV for execution;
* Each AGV can only perform one task at a time, and a task can and can only be performed once by one AGV;
* This article assumes that the AGV system adopts a centralized control method, and the tasks of each AGV come from the host computer, and each AGV communicates with the host computer, and there is no information exchange between AGVs.

According to the type of operation, the AGV system can be composed of three modules: task generation module, task allocation module and path planning module. As the warehouse continuously receives new orders, the task generation module continuously generates new tasks, continuously performs task allocation and path planning. The overall operation process of the AGV system is as follows:

1. **Task generation**: The host computer receives warehouse orders, converts them into tasks executable by AGV, generates a task set, and deletes the task from the task set after the task is completed.
2. **Task allocation**: The goal of this template is to ensure that the total task completion time is the shortest when each task is completed satisfactorily. Under certain task sequence optimization rules, combined with the priority of the task, the task instructions are conveyed to the AGV. In addition, task allocation also needs to consider the balanced operation of each AGV to avoid the life of some AGVs being reduced due to excessively heavy tasks. Since the operation of AGV is time-continuous, the task allocation module conveys a task sequence to the AGV, and the AGV executes tasks in sequence according to this sequence.
3. **Path planning**: In actual situations, a warehouse often has multiple AGVs. The most important thing about the path planning module is to reasonably plan the path for each AGV. When the AGV receives a specific task, it first needs to preliminarily plan its walking route, and make necessary adjustments based on the walking conditions of other AGVs to avoid collisions or deadlocks.

#### 类设计 Class design

##### Map类 

* 从文件中导入仓库位置点与路径

* 可以使用图存放仓库位置点与路径集

* 可以使用dijkstra算法解出最优路径路径，并根据转弯数由多到少进行排序。

##### AGV类

* 可根据输入参数求解各个AGV自己的路径集

* 从中根据快速、防碰撞两个原则进行路径的选择

* 实时移动

##### Map 

* Import warehouse location points and paths from files

* Use graphs to store warehouse location points and path sets

* Use dijkstra algorithm to solve the optimal path and sort them from most to least according to the number of turns.

##### AGV 

* Solve the path set of each AGV according to the input parameters

* Select the path based on the two principles of fast and anti-collision

* Real-time movement

#### 工程实现 #### Engineering implementation

[代码库/Code](
https://github.com/Superone77/AGV_dijkstra/tree/master/code)


