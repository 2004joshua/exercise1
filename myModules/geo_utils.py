import math
import re
import numpy as np
from scipy.spatial import KDTree

# Earth's radius in kilometers
EARTHS_RADIUS_KM = 6371.0


# Converts degrees to radians
def to_radians(x):
    return x * math.pi / 180.0


# Trims whitespace from a string
def trim(s):
    return s.strip()


# Parses coordinate input and converts to radians
# Parses coordinate input and converts to radians
def parse_coordinates(input_str):
    """
    Parses a coordinate string (e.g., "40.7128° N", "74.0060° W", "40.7128").
    Converts it to radians.

    Returns:
      - Radians value if valid
      - -200 if the string is empty
      - -201 if the string is in an invalid format
      - -202 if the value is out of range
    """
    s = trim(input_str)

    if not s:
        return -200  # Error code for empty string

    # Remove words like "degrees" or other unexpected text
    s = re.sub(r"[^\d.\-°NSEW]", "", s)

    # Match coordinate format
    match = re.match(r"([\d.]+)\s*°?\s*([NSEW]?)", s)

    if match:
        value, direction = match.groups()
        decimal_value = float(value)

        # If direction is S or W, make it negative
        if direction in ["S", "W"]:
            decimal_value *= -1

        return to_radians(decimal_value)

    # If it's already a decimal number, return it as float
    try:
        return to_radians(float(s))
    except ValueError:
        return -201
    except OverflowError:
        return -202


# Haversine formula (vectorized for efficiency)
def haversine_vectorized(latA, lonA, latB, lonB):
    """
    Computes the Haversine distance between two sets of coordinates.
    All inputs must be in radians.
    """
    dlat = latB - latA
    dlon = lonB - lonA

    a = (
        np.sin(dlat / 2) ** 2 +
        np.cos(latA) * np.cos(latB) * np.sin(dlon / 2) ** 2
    )

    return 2 * EARTHS_RADIUS_KM * np.arctan2(np.sqrt(a), np.sqrt(1 - a))


# Finds the shortest distance using a k-d tree
def shortest_distance_finder(arrayA, arrayB):
    """
    Given two sets of coordinate points, finds the shortest distance from
    each point in arrayA to any point in arrayB using a k-d tree.

    Args:
      arrayA (list of tuples): [(lat1, lon1), (lat2, lon2), ...]
      arrayB (list of tuples): [(lat1, lon1), (lat2, lon2), ...]

    Returns:
      List of shortest distances for each point in arrayA.
    """
    if not arrayA or not arrayB:
        return []  # Avoid processing if either array is empty

    # Convert coordinates to radians **once** for efficiency
    parsed_A = (
        np.array([[
            parse_coordinates(lat),
            parse_coordinates(lon)]
            for lat, lon in arrayA])
    )

    parsed_B = (
        np.array([[
            parse_coordinates(lat),
            parse_coordinates(lon)]
            for lat, lon in arrayB])
    )

    # Handle invalid coordinates **before** building the k-d tree
    if np.any(parsed_A == -200) or np.any(parsed_B == -200):
        print("Empty string inputs detected.")
        return []
    if np.any(parsed_A == -201) or np.any(parsed_B == -201):
        print("Invalid input coordinates detected.")
        return []
    if np.any(parsed_A == -202) or np.any(parsed_B == -202):
        print("Out of range coordinates detected.")
        return []

    # Build the k-d tree for fast nearest neighbor search
    tree = KDTree(parsed_B)

    # Find the nearest neighbor for each point in arrayA
    _, indices = tree.query(parsed_A, k=1)  # k=1 → find closest neighbor

    # Compute distances using the Haversine formula
    distances = [
        haversine_vectorized(
            parsed_A[i, 0],
            parsed_A[i, 1],
            parsed_B[idx, 0],
            parsed_B[idx, 1])

        for i, idx in enumerate(indices)
    ]

    return distances


# Prints distances as a formatted list
def print_distances(distances):
    """
    Prints a list of distances in a readable format.
    Example: [12.34, 45.67, 89.10]
    """
    print("[", ", ".join(map(lambda d: f"{d:.2f}", distances)), "]")
