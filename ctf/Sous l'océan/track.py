#!/usr/bin/env python3

import gpxpy.gpx  # pip3 install gpxpy
import re
from pathlib import Path
from turtle import *


gpx = gpxpy.gpx.GPX()

gpx_track = None
gpx_segment = None
points = []

for line in open("memdump.txt"):

    if line.strip().startswith("Custom Location"):
        if gpx_segment:
            gpx_track.segments.append(gpx_segment)

        gpx_track = gpxpy.gpx.GPXTrack()
        gpx.tracks.append(gpx_track)
        gpx_segment = gpxpy.gpx.GPXTrackSegment()

    gps = re.search(r"gps (-?\d+\.\d+) (-?\d+\.\d+)", line)
    if not gps:
        gps = re.search(r"gps (-?\d+,\d+)\s(-?\d+,\d+)", line)

    if gps:
        lat, lon = gps.groups()
        lat = lat.replace(",", ".")
        lon = lon.replace(",", ".")
        gpx_segment.points.append(gpxpy.gpx.GPXTrackPoint(lat, lon, elevation=0))

        points.append((float(lat), float(lon)))

gpx_track.segments.append(gpx_segment)

Path("track.gpx").write_text(gpx.to_xml())


llx = min(lat for lat, _ in points)
ulx = max(lat for lat, _ in points)
lly = min(lon for _, lon in points)
uly = max(lon for _, lon in points)

setworldcoordinates(-0.5, -0.5, 10.5, 10.5)

speed("fastest")

for line in open("memdump.txt"):
    if line.strip().startswith("Custom Location"):
        penup()

    gps = re.search(r"gps (-?\d+\.\d+) (-?\d+\.\d+)", line)
    if not gps:
        gps = re.search(r"gps (-?\d+,\d+)\s(-?\d+,\d+)", line)
    if gps:
        lat, lon = gps.groups()
        lat = float(lat.replace(",", "."))
        lon = float(lon.replace(",", "."))

        print(lat, lon)

        lat = (lat - llx) / (ulx - llx) * 10
        lon = (lon - lly) / (uly - lly) * 10

        goto(lat, lon)
        pendown()

done()
