# Graph Extractor from Spice Netlist & Euler Path Generator

This repository cointains source code that is aimed at converting a spice netlist (digital) to its corresponding layout. The layout is generated using the Open Source Tool named Magic. Here, **fn.sp** contains the spice netlist of the function **Y = ~[(B+D).(A+C)+(E.F)].** 
We're trying to automatically generate layout for this boolean fuction. This project is initially built for digital circuits and later to be scaled/modified for analog circuits. 

**The project is in a very early stage and might not yet be ready for productive use.**

**Assumptions** -- The Design Engineer/Characterization Engineer has designed the circuit and performed the circuit simulations and has generated the spice netlist. A tutorial on how to perform circuit simulations using **ngspice** can be found [**here**](https://github.com/sherylcorina/avsdbgp_3v3). 

A very brief description of this project can be found [**here**](https://www.vlsisystemdesign.com/ip/). This work has been carried out by going through Mr. Kunal Ghosh's lecture on Custom Layout. You can have a look at the course [**here**](https://www.udemy.com/course/vlsi-academy-custom-layout/).

## Description

1. The first step is to extract the graph information (edges & nodes etc) from the spice netlist.
<p align="center">
  <img width="750" height="400" src="Images/ckt_layout.png">
</p>

2. The second step is to generate the Euler Path (common to both PMOS & NMOS networks) from the graph for optimal placement of Poly's.
<p align="center">
  <img width="750" height="400" src="Images/ckt_layout1.png">
</p>

3. Next, we paint the layout using the stick diagram.
<p align="center">
  <img width="750" height="400" src="Images/ckt_layout2.png">
</p>
<p align="center">
  <img width="750" height="400" src="Images/ckt_layout3.png">
</p>
4. Final Step - DRC Check/Clean
<p align="center">
  <img width="750" height="400" src="Images/ckt_layout4.png">
</p>

**Note** -- There are some pre-requisites to understand/reproduce this project.

1. Working Knowledge of Data Structures and Algorithms in any programming language. I have used C++ here. 
2. Knowledge of Graphs.
3. Knowledge of grep/awk/sed & tcl.

You can get proficient in programming by following the steps given [**here**](https://medium.com/@sethupathibalakrishnan/my-experiences-on-anything-and-everything-in-life-231eb4699609) in the Competitive Programming Section. A tutorial on finding the Euler Path can be found [**here**](https://www.youtube.com/watch?v=8MpoO2zA2l4&t=11s).
The layouts are drawn using Magic Layout Tool. Installation instructions can be found [**here**](https://www.udemy.com/course/vsd-a-complete-guide-to-install-open-source-eda-tools/).
## Conventional Work Flow

<p align="center">
  <img width="750" height="400" src="Images/Untitled presentation-2.jpg">
</p>

It takes enormous amount of time to calculate the positions of each component like distance between the poly, total height & width of the cell, spacing between the cells etc and draw the layout adhering to the DRC rules.
This project is an attempt to reduce the **Engineering Effort** that is put in drawing the layout. 

## Layout Generation Engine (An abstract flow diagram)

<p align="center">
  <img width="750" height="450" src="Images/flow_with_PDK.png">
</p>

A brief document on this layout_generator flow can be found [**here**](Documentation/Layout_generator.pdf). 

## Euler Path Existence (pseudo-code)
**Input : Graph containing vertices and edges**.<br/>
**Output : Returns Euler Path Existence**.<br/>
There are basically 4 methods. (Note: This is the pseudo code for Euler Path Existence and not for Euler Path Generation.)

1. addEdge
2. DFS
3. isConnected
4. isEulerean

---------------------
***0. Initialize graph 'adj' and no. of Vertices V***<br/>
***1. addEdge(node1, node2)***<br/> <br/>
***2. DFS(vertex, visited[])***<br/>
***3. visited[vertex] <- true***     //Mark the current node as visited <br/>
***4. list <*** ***int> :: iterator node*** //initialize iterator to adjacency list <br/>
***5. foreach (node in adj)*** <br/>
***6. if(!visited[i])*** <br/>
***7. DFS(i,visited)*** //recursive call <br/> <br/>
***8. isConnected()*** //method to check if the graph is connected<br/>
***9. foreach (i in V)*** <br/>
***10. visited[i] <- false*** //mark all nodes as not visited <br/>
***11. foreach(i in V)*** //Find vertex with non-zero degree <br/>
***12. if (adj[i].size() != 0) break;*** <br/>
***13. if(i==V) return true***   
***14. DFS(i,visited)*** <br/>
***15. foreach(i in V)*** <br/>
***16. if(visited[i]==false & adj[i].size>0) return false else return true*** <br/><br/>
***17. isEulerean()*** <br/>
***18. if(isConnected==false) return 0*** <br/>
   
/* 0 --> If graph is not Eulerian <br/>
   1 --> If graph has an Euler path (Semi-Eulerian) <br/>
   2 --> If graph has an Euler Circuit (Eulerian) */<br/><br/> 
***19. foreach(i in V)***   
***20. if(adj[i].size() & 1) odd++***      
***21. if(odd>2) return 0 else return (odd)?1:2***      
   
---------------------
## Details

Step 0 -- Clone the repository
```
$  git clone https://github.com/sethupathib/final_layout_generator.git
```

Step 1 -- Extract edges/node information from the spice netlist.
The edges and node details are extracted from the Netlist using grep+awk+sed. (There is some work that is to be done here).
The shell script to extract the node/edge details can be found [**here**](Source_Code/read_spice.sh). 
The extracted file has to be further processed to feed the algorithm to get the Euler Trail. (Work Pending)

- Change directory to "Execution"
```
$  cd Execution
```
- Run the shell script.
```
$  source read_spice.sh
```
- You get the following ouput.
<p align="center">
  <img width="750" height="300" src="Images/output1.png">
</p>

- Input & Output File Comparison
<p align="center">
  <img width="750" height="400" src="Images/output2.png">
</p>

- This output file needs some more processing to be fed to the algorithm. (I'm currently work on this right now). Comparison of the obtained file and the file format that the algorithm requires -->
<p align="center">
  <img width="750" height="450" src="Images/compare1.png">
</p>



Step 2 -- Feed the extracted file to the Euler Trail finding algorithm. Source code for the algorithm can be found [**here**](Source_Code/EulerTrail.cpp).
The algorithm takes majorly 2 values. They are -->
1. Total number of edges.
2. The Edge List.

Command to run the algorithm is as follows.
```
$  g++ EulerTrail.cpp -o EulerTrail
```

```
$  ./EulerTrail < inputs.txt
```

You get the following output. This is the Euler Path for the combined graph
<p align="center">
  <img width="900" height="50" src="Intermediate_Outputs/sample_output.png">
</p> 

   
 ##  Pending Work
 
 - The file conversion needs to be worked upon. 
 - Graph Splitting. Need to go through this. It's very important. As of this moment, the algorithm only returns the Euler Path for the Combined (PMOS + NMOS) graph.  
 - Layouting.
 - Routing the Layout. (This seems to an extremely difficult task mainly because it is done after placing the poly's in the design)
 - Pass Transistor's. Layouting for pass transistor logic is a bit complicated as it requires adding dummy nodes/edges and forming the graph.
 - Random Graph Generator (This is important for testing the algorithm)
 - To know more about bridges and articulation points in a graph. 
 - I need to solve a lot of problems and get to know about some advanced concepts like Dynamic Programming and Memoization applied on graphs.

## Note

 - This project was initially aimed at generating Analog Layouts. However, that seemed to be an Herculean task. So, we tried for Digital Layouts. There are still a lot of things to be done. (Layouts for various PDK's, DRC's etc). While researching about this, we discovered another project that does the exact same thing. You can find it [**here**](https://github.com/ALIGN-analoglayout/ALIGN-public). This is a massive project involving multi-org & multi-institutional NDA's and top researchers in the world and  funded by DARPA, Department of Defense, USA.
 - A usable version of this software is available [**here**](https://codeberg.org/tok/librecell). It has been developed by Thomas Kramer. (PhD @ ETH-Zurich).
 - This objective of this project is to replicate the work done by Thomas thereby getting an exponential learning curve.
 - The usage of the tool is quite basic. However, developing the entire toolchain from scratch was a major challenge. 
 - A CS grad can crack this problem with a little effort. However, I am not from CS. Hence, it took me a lot of time to get acquainted with CS concepts.
 - Euler Path finding problem is a DIV-2/D problem on codeforces.com.
 - [**Euler Path Finding on a Undirected Graph.**](https://cp-algorithms.com/graph/euler_path.html)

 
## Author

**Sethupathi Balakrishnan, Ex-Qualcomm P&R Engineer**

## Acknowledgments
- Kunal Ghosh, Director, VSD Corp. Pvt. Ltd.
- Philipp Gühring, Software Architect, LibreSilicon Assocation

Contact Information
===================================
- Sethupathi Balakrishnan, SoC Design Engineer, b.sethupathi@gmail.com
- Kunal Ghosh, Director, VSD Corp. Pvt. Ltd. kunalghosh@gmail.com
- Philipp Gühring, Software Architect, LibreSilicon Assocation, pg@futureware.at
