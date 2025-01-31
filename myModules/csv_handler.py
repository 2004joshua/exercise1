import csv


def read_csv(filepath):
    """
    Reads a CSV file and dynamically detects latitude & longitude columns,
    even if they have different spellings (e.g., 'lat', 'latitude', 'LAT',
    etc.).
    Returns:
      - List of tuples [(lat, lon), (lat, lon), ...] or None if an error
      occurs.
    """
    coordinates = []

    LAT_VARIANTS = {"latitude", "lat", "lat."}
    LON_VARIANTS = {"longitude", "lon", "long", "lon."}

    try:
        with open(filepath, newline='', encoding="utf-8") as csvfile:
            reader = csv.reader(csvfile)
            headers = next(reader)  # Read the header row

            headers = [h.lower().strip() for h in headers]  # Normalize headers

            # Find column indices dynamically
            lat_idx = lon_idx = None
            for i, h in enumerate(headers):
                if h in LAT_VARIANTS:
                    lat_idx = i
                elif h in LON_VARIANTS:
                    lon_idx = i

            if lat_idx is None or lon_idx is None:
                print(
                  "Error: Could not find latitude/longitude columns in {}"
                  .format(filepath))
                return None

            # Read coordinate data into a list
            for row in reader:
                # Ensure row has required columns
                if len(row) > max(lat_idx, lon_idx):
                    coordinates.append((row[lat_idx].strip(),
                                        row[lon_idx].strip()))

    except Exception as e:
        print("Error reading file {}: {}".format(filepath, e))
        return None

    return coordinates
