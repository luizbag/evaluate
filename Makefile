# evaluate
# 
# Makefile
# 


PROGRAM_NAME=evaluate
CC=g++
CFLAGS=
#INCLUDE=-I /home/lasid/programs/auxiliares/boost_1_55_0
LIBS := -lboost_system -lboost_filesystem
#LIBS2 = -L /home/lasid/programs/auxiliares/boost_1_55_0/stage/lib/

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
./ValidationIndex/CRIndex.cpp \
./ValidationIndex/Connectivity.cpp \
./ValidationIndex/Deviation.cpp \
./ValidationIndex/Variance.cpp \
./ValidationIndex/FMeasure.cpp \
./ValidationIndex/NMIIndex.cpp \
./ValidationIndex/Silhouette.cpp \
./ValidationIndex/VIIndex.cpp \
./Cluster.cpp \
./DataExplorer.cpp \
./DataSet.cpp \
./Euclidean.cpp \
./Exception.cpp \
./InformationTheory.cpp \
./NnList.cpp \
./Object.cpp \
./Partition.cpp \
./Pearson.cpp \
./RelationSDN.cpp \
./Similarity.cpp \
./SimilarityMatrix.cpp \
./ValidationIndex.cpp \
./main.cpp 


OBJS = \
./ValidationIndex/CRIndex.o \
./ValidationIndex/Connectivity.o \
./ValidationIndex/Deviation.o \
./ValidationIndex/Variance.o \
./ValidationIndex/FMeasure.o \
./ValidationIndex/NMIIndex.o \
./ValidationIndex/Silhouette.o \
./ValidationIndex/VIIndex.o \
./Cluster.o \
./DataExplorer.o \
./DataSet.o \
./Euclidean.o \
./Exception.o \
./InformationTheory.o \
./NnList.o \
./Object.o \
./Partition.o \
./Pearson.o \
./RelationSDN.o \
./Similarity.o \
./SimilarityMatrix.o \
./ValidationIndex.o \
./main.o 


all:
	$(CC) $(CFLAGS) $(INCLUDE) -o "evaluationIndices" $(CPP_SRCS) $(LIBS2) $(LIBS)
