import numpy
import scipy.stats
import math
import sys

if __name__ == '__main__':
    filename = sys.argv[1]
    descriptor = open(filename, "r")

    sample = []
    for line in descriptor:
        if line:
            sample.append(float(line.strip()))

    descriptor.close()
    
    length = len(sample)
    if length < 2:
        sys.exit()

    mean = numpy.mean(sample)
    summary = numpy.sum(sample)

    dispersion = 0
    for element in sample:
        dispersion += (element - mean) ** 2;
    
    dispersion /= length - 1 

    radius = scipy.stats.t.ppf((1 + 0.9) / 2, length - 1) * scipy.stats.sem(sample) / math.sqrt(length)

    print("Count - %d.\nTotal - %f ms.\nMean - %f ms.\nDispersion - %f.\nRadius - %f ms.\nInterval - [%f ms, %f ms]." % (length,  summary, mean, dispersion, radius, mean - radius, mean + radius))
