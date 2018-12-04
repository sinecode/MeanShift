# go to the script's directory
cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null

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
logFile="$(date "+%d-%m-%Y_%T").log"
datasetsDir="./datasets"


# execute the sequential batch test and write its output to the log file
echo "Executing the sequential version..."
"$seqExePath" 1 \
"$datasetsDir/data1.csv" 1 \
"$datasetsDir/data2.csv" 1 \
"$datasetsDir/data3.csv" 1 \
"$datasetsDir/data4.csv" 1 \
"$datasetsDir/data5.csv" 1 \
"$datasetsDir/data6.csv" 1 \
"$datasetsDir/data7.csv" 1 \
"$datasetsDir/data8.csv" 1 \
"$datasetsDir/data9.csv" 1 \
"$datasetsDir/data10.csv" 1 \
> "$logFile"

elapsedTimeSeq=$(tail -n 1 "$logFile" | awk '{print $4}')
echo "Elapsed time of the sequential version: $elapsedTimeSeq s"

numProc=$(nproc)

# execute the parallel version with a different number of threads
for nthreads in \
$(seq 2 $numProc ; seq $(( $numProc + 1 )) 3 $(( $numProc + 10 ))); do
    # execute the parallel batch test and append its output to the log file
    echo "Executing the parallel version with $nthreads threads..."
    "$parExePath" $nthreads \
    "$datasetsDir/data1.csv" 1 \
    "$datasetsDir/data2.csv" 1 \
    "$datasetsDir/data3.csv" 1 \
    "$datasetsDir/data4.csv" 1 \
    "$datasetsDir/data5.csv" 1 \
    "$datasetsDir/data6.csv" 1 \
    "$datasetsDir/data7.csv" 1 \
    "$datasetsDir/data8.csv" 1 \
    "$datasetsDir/data9.csv" 1 \
    "$datasetsDir/data10.csv" 1 \
    >> "$logFile"

    elapsedTimePar=$(tail -n 1 "$logFile" | awk '{print $4}')
    echo "Elapsed time of the parallel version: $elapsedTimePar s"

    # Speedup is time_sequential_version / time_parallel_version.
    # Ideally should be equal to the number of processors used to execute the
    # parallel version
    speedup=$(echo $elapsedTimeSeq $elapsedTimePar | awk '{print $1/$2}')
    echo "Speedup with $nthreads threads: $speedup" >> "$logFile"
    echo "Speedup with $nthreads threads: $speedup"
done
