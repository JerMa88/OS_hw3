# makefile for scheduling program
#
# make rr - for round-robin scheduling
# make fcfs - for FCFS scheduling
# make sjf - for SJF scheduling
# make priority - for priority scheduling
# make priority_rr - for priority with round-robin scheduling

CC=gcc
CFLAGS=-Wall

clean:
	rm -rf *.o
	rm -rf fcfs
	rm -rf sjf
	rm -rf rr
	rm -rf priority
	rm -rf priority_rr

rr: driver.o list.o CPU.o schedule_rr.o schedulers.o
	$(CC) $(CFLAGS) -o rr driver.o schedule_rr.o list.o CPU.o schedulers.o

sjf: driver.o list.o CPU.o schedule_sjf.o schedulers.o
	$(CC) $(CFLAGS) -o sjf driver.o schedule_sjf.o list.o CPU.o schedulers.o

fcfs: driver.o list.o CPU.o schedule_fcfs.o schedulers.o
	$(CC) $(CFLAGS) -o fcfs driver.o schedule_fcfs.o list.o CPU.o schedulers.o

priority: driver.o list.o CPU.o schedule_priority.o schedulers.o
	$(CC) $(CFLAGS) -o priority driver.o schedule_priority.o list.o CPU.o schedulers.o

priority_rr: driver.o list.o CPU.o schedule_priority_rr.o schedulers.o
	$(CC) $(CFLAGS) -o priority_rr driver.o schedule_priority_rr.o list.o CPU.o schedulers.o

driver.o: driver.c
	$(CC) $(CFLAGS) -c driver.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

CPU.o: CPU.c cpu.h
	$(CC) $(CFLAGS) -c CPU.c

schedulers.o: schedulers.c schedulers.h
	$(CC) $(CFLAGS) -c schedulers.c

schedule_fcfs.o: schedule_fcfs.c schedulers.h
	$(CC) $(CFLAGS) -c schedule_fcfs.c

schedule_sjf.o: schedule_sjf.c schedulers.h
	$(CC) $(CFLAGS) -c schedule_sjf.c

schedule_priority.o: schedule_priority.c schedulers.h
	$(CC) $(CFLAGS) -c schedule_priority.c

schedule_rr.o: schedule_rr.c schedulers.h
	$(CC) $(CFLAGS) -c schedule_rr.c

schedule_priority_rr.o: schedule_priority_rr.c schedulers.h
	$(CC) $(CFLAGS) -c schedule_priority_rr.c
