# 
# Copyright © 2022 de Argel Capela, Todos os direitos reservados
#

clear

#banner
echo
echo -e "\e[1;32m*********************************************** \e[0m"
echo -e "\e[1;32m*                                             * \e[0m"
echo -e "\e[1;32m*       42-PHILOSOPHERS CAPELA TESTER         * \e[0m"
echo -e "\e[1;32m*                                             * \e[0m"
echo -e "\e[1;32m*              \e[0m\e[0;32margelcapela.com\e[0m \e[1;32m               *\e[0m"
echo -e "\e[1;32m*                                             * \e[0m"
echo -e "\e[1;32m*********************************************** \e[0m"
echo
sleep 2

# global config
#philo_dir="../../alexei-philosopher/philop3/philo/"
philo_dir="../app/philo/"
exec=$philo_dir"philo"
time=0.3

# design
sucess="";
fail="";

# check test mode
argc=$#
specific=0
if (($argc > 0));
then    
    argv=$@
    specific=${argv[0]}
fi

# update app
make re -C $philo_dir


#######################################################
#                                                     #
#                      Test 1                         #
#                                                     #
#######################################################
x=0
repeat=2

if ((specific == 0 || (specific > 0 && specific == 1)));
then
echo
echo -e "\e[0;33mTest 1 - The philosopher should not eat and should die:\e[0m"
echo
while [ $x -le $(($repeat - 1)) ]
do
    echo "$(($x + 1)) ./philo 1 800 200 200)"
    echo -e
    $exec 1 800 200 200

    echo -e
    sleep $time
    x=$(($x + 1))
done
echo
echo
fi

#######################################################
#                                                     #
#                      Test 2                         #
#                                                     #
#######################################################
x=0
repeat=2

if ((specific == 0 || (specific > 0 && specific == 2)));
then
echo
echo -e "\e[0;33mTest 2 - No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times:\e[0m"
echo
while [ $x -le $(($repeat - 1)) ]
do
    echo
    echo
    echo "$(($x + 1)) ./philo 5 800 200 200 7)"
    echo -e
    $exec 5 800 200 200 7
    echo -e
    sleep $time
    x=$(($x + 1))
done
echo
echo
fi

#######################################################
#                                                     #
#                      Test 3                         #
#                                                     #
#######################################################
x=0
repeat=30
short_mode=0

if ((specific == 0 || (specific > 0 && specific == 3)));
then
echo
echo -e "\e[1;33mTest 3 - One philosopher should die:\e[0m"
echo
n_s=0
n_f=0
while [ $x -le $(($repeat - 1)) ]
do
    params="4 310 200 100"
    # calc diff between last and before last time is bigger than 10ms
    output=$($exec $params | tail -2)
    n1=$(echo "$output" | tail -2 | head -1 | awk '{print $1;}')
    n2=$(echo "$output" | tail -1 | head -1 | awk '{print $1;}')
    diff=$(($n1 + 10))
    if (($n2 > $diff))
    then
        start_color="[1;31m"
        t_res="FAIL (died "$(($n2 - $diff))"ms more than necessary)"
        n_f=$(($n_f + 1))
    else
        start_color="[1;32m"
        t_res="SUCCESS"
        n_s=$(($n_s + 1))
    fi
    echo -e "\e$start_color$(($x + 1))) ./philo $params "$t_res"\e[0m"
    echo
    echo "$output"
    sleep $time
    echo
    #valgrind --leak-check=full $exec $params
    #sleep $time
    x=$(($x + 1))
done
echo -e "\e[1;33mTest 3 - Tested "$repeat" times - Result:\e[0m"
echo -e "\e[1;31mfail: "$n_f"\e[0m"
echo -e "\e[1;32msuccess: "$n_s"\e[0m"
echo
fi

#######################################################
#                                                     #
#                      Test 4                         #
#                                                     #
#######################################################
limit=1
x=0
repeat=2

if ((specific == 0 || (specific > 0 && specific == 4)));
then
echo
echo -e "\e[0;33mTest 4 - No philosopher should die:\e[0m"
echo
while [ $x -le $(($repeat - 1)) ]
do
    echo "$(($x + 1))) ./philo 4 410 200 200 $limit"
    echo -e
    $exec 4 410 200 200 $limit
    sleep $time
    x=$(($x + 1))
done
fi

#######################################################
#                                                     #
#                      Test 5                         #
#                                                     #
#######################################################
limit=1
x=0
repeat=2

if ((specific == 0 || (specific > 0 && specific == 5)));
then
echo
echo -e "\e[0;33mTest 5 - No philosopher should die:\e[0m"
echo
while [ $x -le $(($repeat - 1)) ]
do
    echo -e "\e[0;33m$(($x + 1))) ./philo 5 800 200 200 $limit\e[0m"
    echo -e
    $exec 5 800 200 200 $limit
    echo -e
    sleep $time
    x=$(($x + 1))
done
echo
echo
fi
