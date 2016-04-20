launch-part1-qemu:
	(cd Part1; make launch-qemu)
launch-part1-gdb:
	(cd Part1; make launch-gdb)
clean-part1:
	(cd Part1; make clean)


launch-part2-IPC-qemu:
	(cd Part2-IPC; make launch-qemu)
launch-part2-IPC-gdb:
	(cd Part2-IPC; make launch-gdb)
clean-part2-IPC:
	(cd Part2-IPC; make clean)


launch-part2-round-qemu:
	(cd Part2-rr; make launch-qemu)
launch-part2-round-gdb:
	(cd Part2-rr; make launch-gdb)
clean-part2-round:
	(cd Part2-rr; make clean)

launch-part2-shell-qemu:
	(cd Part2-shell; make launch-qemu)
launch-part2-shell-gdb:
	(cd Part2-shell; make launch-gdb)
clean-part2-shell:
	(cd Part2-shell; make clean)


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
disk-part3:
	(cd Part3; cd device; python disk.py --host=127.0.0.1 --port=1235 --file=disk.bin --block-num=65536 --block-len=16 )
reset-disk:
	(cd Part3; cd device; dd of=disk.bin if=/dev/zero count=1048576 bs=1)
view-disk:
	(cd Part3; cd device; hexdump -C disk.bin)

clean-all: clean-part1 clean-part2-round clean-part2-shell clean-part2-priority clean-part2-IPC clean-part3
