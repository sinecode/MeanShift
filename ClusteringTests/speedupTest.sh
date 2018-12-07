# go to the script's directory
cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null

rm -rf build*

# compile the sequential version
buildSeqDir="build-seq"
mkdir -p $buildSeqDir
cd $buildSeqDir
cmake -DCMAKE_BUILD_TYPE=Release ../../MeanShift/
make -j $(nproc)
cd - > /dev/null
seqExePath="$buildSeqDir/batchtest"

# compile the parallel version
buildParDir="build-par"
mkdir -p $buildParDir
cd $buildParDir
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=-fopenmp ../../MeanShift/
make -j $(nproc)
cd - > /dev/null
parExePath="$buildParDir/batchtest"

# create a .log file with name "date_time.log"
logFile="$(date "+%d%m%Y_%H%M%S").log"
datasetsDir="./datasets"

# string to display finally with the results of the speedups
endOutput="========================================================="
endOutput="$endOutput\nNumber of processors: $(nproc)"
endOutput="$endOutput\n"

# execute the sequential batch test and write its output to the log file
echo "Executing the sequential version..."
"$seqExePath" 1 \
"$datasetsDir/randData.csv" 3 \
> "$logFile"

elapsedTimeSeq=$(tail -n 1 "$logFile" | awk '{print $4}')
endOutput="$endOutput\nSequential: $elapsedTimeSeq s"
echo "Sequential version: $elapsedTimeSeq s"

numProc=$(nproc)

# execute the parallel version with a different number of threads
for nthreads in \
$(seq 2 $numProc ; seq $(( $numProc + 1 )) 3 $(( $numProc + 10 ))); do
    # execute the parallel batch test and append its output to the log file
    echo "Executing the parallel version with $nthreads threads..."
    "$parExePath" $nthreads \
    "$datasetsDir/randData.csv" 3 \
    >> "$logFile"

    elapsedTimePar=$(tail -n 1 "$logFile" | awk '{print $4}')
    echo "Parallel version with $nthreads threads: $elapsedTimePar s"

    # Speedup is time_sequential_version / time_parallel_version.
    # Ideally should be equal to the number of processors used to execute the
    # parallel version
    speedup=$(echo $elapsedTimeSeq $elapsedTimePar | awk '{print $1/$2}')
    endOutput="$endOutput\n==========================================="
    endOutput="$endOutput\nParallel version with $nthreads threads: $elapsedTimePar s"
    endOutput="$endOutput\nSpeedup with $nthreads threads: $speedup"
    echo "Speedup with $nthreads threads: $speedup" >> "$logFile"
    echo "Speedup with $nthreads threads: $speedup"
done
printf %b "$endOutput\n" >> "$logFile"
