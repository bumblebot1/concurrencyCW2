launch-part1-qemu:
	(cd Part1; make launch-qemu)
launch-part1-gdb:
	(cd Part1; make launch-gdb)
clean-part1:
	(cd Part1; make clean)


launch-part2-IPC-qemu:
	(cd Part2-IPC; make launch-qemu)
launch-part1-IPC-gdb:
	(cd Part2-IPC; make launch-gdb)
clean-part2-IPC:
	(cd Part2-IPC; make clean)


launch-part2-rr-qemu:
	(cd Part2-rr; make launch-qemu)
launch-part2-rr-gdb:
	(cd Part2-rr; make launch-gdb)
clean-part2-rr:
	(cd Part2-rr; make clean)


launch-part2-priority-qemu:
	(cd Part2-pr; make launch-qemu)
launch-part2-priority-gdb:
	(cd Part2-pr; make launch-gdb)
clean-part2-priority:
	(cd Part2-pr; make clean)


launch-part3-qemu:
	(cd Part3; make launch-qemu)
launch-part3-gdb:
	(cd Part3; make launch-gdb)
clean-part3:
	(cd Part3; make clean)
