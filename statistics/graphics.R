# loop times 
executionTimeInSeconds <- c(55.570761,27.850214,13.930710,7.019160, 4.348725,2.580024, 2.741145 )
round(executionTimeInSeconds,digits=3)
numberOfThreads <-c()

for(i in 0:6) numberOfThreads[i+1]= 2^(i)

# version 1
# 
# plot(x=numberOfThreads,y=executionTimeInSeconds,xlab="# threads",
#      ylab="t in sec",type="o",col="red")
# 
# # Create a title with a red, bold/italic font
# title(main="execution times different # threads", font.main=4)


#version 2

plot(executionTimeInSeconds, ylab="t in sec",type="b",col="red",xlab="# threads",xaxt = "n")

axis(1,at=1:7, lab=numberOfThreads)
title(main="execution times overview", font.main=4)


#calculate speedup 
tn <- executionTimeInSeconds[1]
speedUp <-tn/executionTimeInSeconds

plot(speedUp, ylab="speed up s(n,p)",type="b",col="red",xlab="# threads",xaxt = "n")

axis(1,at=1:7, lab=numberOfThreads)
title(main="speed up", font.main=4)