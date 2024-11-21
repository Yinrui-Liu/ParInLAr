import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

# Load the data
first_event_data = []
with open("output.txt", "r") as file:
    in_event = False  # Flag to check if we're reading the first event
    for line in file:
        line = line.strip()
        if line.startswith("###"):  # Detect event header
            if in_event:  # If we have already read one event, stop
                break
            in_event = True  # Start reading the first event
        elif in_event:  # Read data lines for the first event
            first_event_data.append([float(x) for x in line.split()])
#arr = np.loadtxt("output.txt")
arr = np.array(first_event_data)
x = arr[:, 0]
y = arr[:, 1]
z = arr[:, 2]
e = arr[:, 3] # Energy deposition
t = arr[:, 4] # Global time

# Define the range for visible points
vmin, vmax = 1e-1, 1e1
print(f"Edep_min {np.min(e):.3g} MeV; Edep_max {np.max(e):.3g} MeV\nSet vmin, vmax = {vmin}, {vmax} MeV\n")

# Mask values outside the range
mask = (e >= vmin) #& (e <= vmax)
x_visible = x[mask]
y_visible = y[mask]
z_visible = z[mask]
e_visible = e[mask]
t_visible = t[mask]
print(f"Total energy deposition {np.sum(e_visible)} MeV")
print(f"Number of points {len(e)} ({len(e_visible)} used)")

# Create a 3D scatter plot
fig = plt.figure()
ax = fig.add_subplot(projection='3d')

# Custom normalization for the color scale
#norm = mcolors.Normalize(vmin=vmin, vmax=vmax)
norm = mcolors.LogNorm(vmin=vmin, vmax=vmax)

# Custom colormap: yellow to red
cmap = mcolors.LinearSegmentedColormap.from_list("YellowToRed", ["yellow", "red"])

# Plot the visible points
sc = ax.scatter(z_visible, x_visible, y_visible, c=e_visible, cmap=cmap, norm=norm)

# Add a colorbar
cbar = plt.colorbar(sc, ax=ax, label='Deposited energy (MeV)')
#cbar.set_ticks([1e-4, 1e-3, 1e-2, 1e-1, 1, 1e1])
ax.set_xlabel('Z (mm)')
ax.set_ylabel('X (mm)')
ax.set_zlabel('Y (mm)') # vertical
ax.set_xlim([-600, 600])
ax.set_ylim([-600, 600])
ax.set_zlim([-600, 600])
#ax.set_title("1 GeV proton in liquid argon")

# Save the plot
#plt.savefig("draw.png")
plt.show()
plt.clf()
