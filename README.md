# M3AP-Jcalford-Adoudkin

![alt text](./images/ordered_depths.png)
![alt text](./images/random_depths.png)


### The first graph displays the node depths for ordered insertion of values 1-100. 
- It can be seen that on the Binary search 
tree the depth is increasing linearly. This is because when a new value is added it creates a linked list like Tree.
- On the other hand the AVL tree is self balancing therefore the trees depth remains constantly low.
- The splay trees depth is linearly decreasing because the splay operations are gradually flatening the tree bringing more
frequently accessed nodes to the top of the tree. 

### The second graph displays the node depths for randomly ordered insertion of values 1-100.

- The node depth for the binary search tree still grows, but it is no longer linearly since the nodes won't make a 
linked list
- The AVL tree remains balanced even with randomly inserted values. This is because it is self-balancing always 
maintaining a node height O(log(O)) height. 
- The splay tree changes according to frequently accessed elements making its depth unpredictable.
