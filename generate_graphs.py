import matplotlib.pyplot as plt
import pandas as pd
import os

# Ensure the 'images' directory exists
os.makedirs("images", exist_ok=True)

# Read data from CSV files in the 'data' folder
ordered_data = pd.read_csv("data/ordered_depths.csv")
random_data = pd.read_csv("data/random_depths.csv")

# Plot for ordered insertion
plt.figure(figsize=(10, 6))
plt.plot(ordered_data["Value"], ordered_data["BST_Depth"], label="BST", marker="o", linestyle="-")
plt.plot(ordered_data["Value"], ordered_data["AVL_Depth"], label="AVL", marker="s", linestyle="-")
plt.plot(ordered_data["Value"], ordered_data["Splay_Depth"], label="Splay", marker="^", linestyle="-")
plt.title("Node Depths for Ordered Insertion (Values 1-100)")
plt.xlabel("Inserted Value")
plt.ylabel("Depth in Tree")
plt.legend()
plt.grid(True)
plt.savefig("images/ordered_depths.png")
plt.show()

# Plot for random insertion
plt.figure(figsize=(10, 6))
plt.plot(random_data["Value"], random_data["BST_Depth"], label="BST", marker="o", linestyle="-")
plt.plot(random_data["Value"], random_data["AVL_Depth"], label="AVL", marker="s", linestyle="-")
plt.plot(random_data["Value"], random_data["Splay_Depth"], label="Splay", marker="^", linestyle="-")
plt.title("Node Depths for Random Insertion (Values 1-100)")
plt.xlabel("Searched Value")
plt.ylabel("Depth in Tree")
plt.legend()
plt.grid(True)
plt.savefig("images/random_depths.png")
plt.show()