g++-13 -std=gnu++17 *.cpp -o borel-equidecomposition -O3
[ -d frames ] && rm -r frames
mkdir -p frames
./borel-equidecomposition 512 512 30 10
rm -f test.mp4
ffmpeg -framerate 30 -pattern_type glob -i 'frames/frame*.ppm' -c:v libx264 -pix_fmt yuv420p test.mp4
rm -r frames
