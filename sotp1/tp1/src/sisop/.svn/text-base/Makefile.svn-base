CLASS_DIR=../../bin
SOURCES = Task.java TaskSet.java TimelinePrinter.java Scheduler.java SchedulerAnalyzer.java FCFS.java MFQ.java MFQIO.java RR.java SJF.java Simulator.java 
OBJS = $(patsubst %.java,$(CLASS_DIR)/sisop/%.class,$(SOURCES))
JAVAC=/usr/lib/jvm/java-6-sun-1.6.0.12/bin/javac

debug:
	@echo $(OBJS)

all: bindir clean binaries

binaries: $(OBJS)

$(OBJS): $(@F:.class=.java)
	$(JAVAC) -cp $(CLASS_DIR) -d $(CLASS_DIR)/ $(@F:.class=.java)

bindir: $(CLASS_DIR)

$(CLASS_DIR):
	mkdir $(CLASS_DIR)

clean:
	find $(CLASS_DIR) -name *.class -delete
