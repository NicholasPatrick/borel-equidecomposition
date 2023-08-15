ffmpeg -framerate 30 -pattern_type glob -i 'frames/frame*.ppm' -c:v libx264 -pix_fmt yuv420p test.mp4
