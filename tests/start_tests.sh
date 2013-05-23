echo "Starting lorem tests..."
./so_tests.sh > results/so_results.txt && echo "Results are in results/so_results.txt"
./file_tests.sh > results/f_results.txt && echo "Results are in results/f_results.txt"
echo "Tests completed."