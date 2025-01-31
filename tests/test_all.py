import sys
import os

# Add the project root directory to sys.path dynamically
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

from myModules.csv_handler import read_csv
from myModules.geo_utils import shortest_distance_finder, print_distances


def main():
    """Runs the test with user-provided CSV files."""
    if len(sys.argv) != 3:
        print("Usage: python test_all.py <fileA.csv> <fileB.csv>")
        sys.exit(1)

    fileA, fileB = sys.argv[1], sys.argv[2]

    print(f"Reading CSV file: {fileA}")
    arrayA = read_csv(fileA)
    print(f"Array A: {arrayA}")

    print(f"Reading CSV file: {fileB}")
    arrayB = read_csv(fileB)
    print(f"Array B: {arrayB}")

    if not arrayA or not arrayB:
        print("Error: One or both CSV files could not be processed.")
        sys.exit(1)

    print("\nComputing shortest distances...")
    distances = shortest_distance_finder(arrayA, arrayB)

    print("\nResults:")
    print_distances(distances)

if __name__ == "__main__":
    main()
