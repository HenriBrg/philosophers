# Mandatory Part

# 5 800 200 200		--> no one should die
# 5 800 200 200 7	--> no one should die and the simulation should stop when
#						all the philosopher has eaten at least 7 times each.
# 4 410 200 200		--> no one should die
# 4 310 200 100		--> a philosopher should die

# Requierement Level

# -easy
# -normal
# -hard

# Validity Thresholds

# 5 800 200 200		--> Last more than 30
# 5 800 200 200 7	--> Just works
# 4 410 200 200		--> Last 10/20/40
# 4 310 200 100		--> Just works

# Usage

# Place this shell script at the root path of the project
#

# ------------------------------------------------------------------------------

T1="5 800 200 200"
T2="5 800 200 200 7"
T3="4 410 200 200"
T4="4 310 200 100"

echo "PHILO_ONE"
make -C philo_one/
philo_one/./philo_one $T1

ps | grep -v grep | grep philo_one
