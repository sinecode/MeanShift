total_points = 10000


# one cluster
data <- rbind(cbind(rnorm(total_points,0,1), rnorm(total_points,0,1)))
write.table(
    data[sample(1:nrow(data)),],
    'datasets/data1.csv', sep=',', col.names=FALSE, row.names=FALSE
)

# two clusters
data <- rbind(
    cbind(rnorm(total_points/2,0,1), rnorm(total_points/2,0,1)),
    cbind(rnorm(total_points/2,5,1), rnorm(total_points/2,5,1))
)
write.table(
    data[sample(1:nrow(data)),],
    'datasets/data2.csv', sep=',', col.names=FALSE, row.names=FALSE
)

# three clusters
data <- rbind(
    cbind(rnorm(total_points/3,0,1), rnorm(total_points/3,0,1)),
    cbind(rnorm(total_points/3,5,1), rnorm(total_points/3,5,1)),
    cbind(rnorm(total_points/3,3,1), rnorm(total_points/3,10,1))
)
write.table(
    data[sample(1:nrow(data)),],
    'datasets/data3.csv', sep=',', col.names=FALSE, row.names=FALSE
)

# four clusters
data <- rbind(
    cbind(rnorm(total_points/4,0,1), rnorm(total_points/4,0,1)),
    cbind(rnorm(total_points/4,5,1), rnorm(total_points/4,5,1)),
    cbind(rnorm(total_points/4,3,1), rnorm(total_points/4,10,1)),
    cbind(rnorm(total_points/4,1,1), rnorm(total_points/4,6,1))
)
write.table(
    data[sample(1:nrow(data)),],
    'datasets/data4.csv', sep=',', col.names=FALSE, row.names=FALSE
)

# five clusters
data <- rbind(
    cbind(rnorm(total_points/5,0,1), rnorm(total_points/5,0,1)),
    cbind(rnorm(total_points/5,5,1), rnorm(total_points/5,5,1)),
    cbind(rnorm(total_points/5,3,1), rnorm(total_points/5,10,1)),
    cbind(rnorm(total_points/5,1,1), rnorm(total_points/5,6,1)),
    cbind(rnorm(total_points/5,-2,1), rnorm(total_points/5,-5,1))
)
write.table(
    data[sample(1:nrow(data)),],
    'datasets/data5.csv', sep=',', col.names=FALSE, row.names=FALSE
)
