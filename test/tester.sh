# 
# Copyright © 2022 de Argel Capela, Todos os direitos reservados
#

clear

#######################################################
#                                                     #
#                  Color Pallets                      #
#                                                     #
#######################################################
success_color="[1;32m"
fail_color="[1;31m"
test_result_color="[1;36m"
banner_color=$success_color

#######################################################
#                                                     #
#                  Banner                             #
#                                                     #
#######################################################
echo
echo -e "\e$banner_color*********************************************** \e[0m"
echo -e "\e$banner_color*                                             * \e[0m"
echo -e "\e$banner_color*       42-PHILOSOPHERS CAPELA TESTER         * \e[0m"
echo -e "\e$banner_color*                                             * \e[0m"
echo -e "\e$banner_color*              \e[0m\e[0;32margelcapela.com\e[0m \e[1;32m               *\e[0m"
echo -e "\e$banner_color*                                             * \e[0m"
echo -e "\e$banner_color*********************************************** \e[0m"
echo
sleep 2

#######################################################
#                                                     #
#                  Global Configs                     #
#                                                     #
#######################################################
#philo_dir="../../alexei-philosopher/philop3/philo/"
philo_dir="../app/philo/"
exec=$philo_dir"philo"
time=0.3

#######################################################
#                                                     #
#                  Parsing Input                      #
#                                                     #
#######################################################
argc=("$#")
argv=("$@")

# Choose a specific test 
specific=0
if (($argc == 1));
then
    specific=${argv[0]}
fi

# Choose a specific test | Set the number of repetitions of it 
repeat=2
if (($argc == 2));
then
    specific=${argv[0]}
    repeat=${argv[1]}
fi

# Choose a specific test | Set the number of repetitions of it 
# and For tests 4 and 5 choose when the simulation ends
max_meals_by_philo=7
if (($argc ==  3));
then
    specific=${argv[0]}
    repeat=${argv[1]}
    max_meals_by_philo=${argv[2]}
fi

# Choose a specific test | Set the number of repetitions of it 
# and For tests 4 and 5 choose when the simulation ends
# and show output
show_output=0
if (($argc ==  4));
then
    specific=${argv[0]}
    repeat=${argv[1]}
    max_meals_by_philo=${argv[2]}
    show_output=${argv[3]}
fi

# fix argv -
[ $specific == "-" ] && specific=0
[ $repeat == "-" ] && repeat=2
[ $max_meals_by_philo == "-" ] && max_meals_by_philo=7

# before start, update the app
make re -C $philo_dir

echo
echo
echo


#######################################################
#                                                     #
#                      Test 1                         #
#                                                     #
#######################################################
x=0
t1_show_output=1
[ $show_output == "0" ] && t1_show_output=0

if (($specific == 0 || ($specific > 0 && $specific == 1)));
then
echo
echo -e "\e[1;33mTest 1 - The philosopher should not eat and should die:\e[0m"
echo
n_s=0
n_f=0
avg_ms_f=0
while [ $x -le $(($repeat - 1)) ]
do
    params="1 800 200 200"
    # calc diff between last and before last time is bigger than 10ms
    output=$($exec $params | tail -2)
    n1=$(echo "$output" | tail -2 | head -1 | awk '{print $1;}')
    n2=$(echo "$output" | tail -1 | head -1 | awk '{print $1;}')
    diff=$(($n1 + 10))
    if (($n2 > $diff))
    then
        start_color="$fail_color"
        t_res="FAIL (died "$(($n2 - $diff))"ms more than necessary)"
        n_f=$(($n_f + 1))
        avg_ms_f=$(($avg_ms_f + $(($n2 - $diff))))
    else
        start_color="$success_color"
        t_res="SUCCESS (died "$(($diff - $n2))"ms after previous action)"
        n_s=$(($n_s + 1))
    fi
    echo -e "\e$start_color$(($x + 1))) ./philo $params "$t_res"\e[0m"
    [ $t1_show_output != "0" ] && echo "$output"
    sleep $time
    x=$(($x + 1))
done
echo
# calc average ms failed
echo -e "\e"$test_result_color"Test 1 - Tested "$repeat" time(s) - Result:\e[0m"
if test $avg_ms_f != 0; 
then
    avg_ms_f=$(($avg_ms_f / $n_f))
    avg="(average of "$avg_ms_f"ms passed)"
else
    avg=""
fi
echo -e "\e"$fail_color"fail: "$n_f" "$avg"\e[0m"
echo -e "\e"$success_color"success: "$n_s"\e[0m"
echo
fi

#######################################################
#                                                     #
#                      Test 2                         #
#                                                     #
#######################################################
x=0
t2_show_output=1
[ $show_output == "0" ] && t2_show_output=0

if (($specific == 0 || ($specific > 0 && $specific == 2)));
then
echo
echo -e "\e[1;33mTest 2 - No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 time(s):\e[0m"
echo
n_s=0
n_f=0
avg_ms_f=0
while [ $x -le $(($repeat - 1)) ]
do
    # calc if each philosophers each in the correct time
    #5 800 200 200 7
    n_philo="2"
    n_must_eat="1"
    params="$n_philo 800 200 200 $n_must_eat"
    output=$($exec $params)
    #echo "Loading the simulation "$(($x + 1))", wait a moment please..."
    for i in $(($n_philo - 1))
    do
        philo_i_n_meals=$(echo "$output" | grep "$i is eating" | wc -l)
         if (($philo_i_n_meals > $n_must_eat));
            then   
                start_color="$fail_color"
                t_res="- FAIL (Philosopher "$i" eated "$philo_i_n_meals" meal(s).This is "$(($philo_i_n_meals - $n_must_eat))" meal(s) more than necessary)"
                n_f=$(($n_f + 1))
                avg_ms_f=$(($avg_ms_f + $(($philo_i_n_meals - $n_must_eat))))
                return
         fi
    done
    if (($n_f == 0));
    then
        start_color="$success_color"
        t_res=" - SUCCESS"
        n_s=$(($n_s + 1))
    fi
    # after calc result, show it
    echo -e "\e$start_color$(($x + 1))) ./philo $params "$t_res"\e[0m"
    [ $t2_show_output != "0" ] && echo "$output"
    sleep $time
    x=$(($x + 1))
done
echo
# calc average ms failed
echo -e "\e"$test_result_color"Test 2 - Tested "$repeat" time(s) - Result:\e[0m"
if test $avg_ms_f != 0; 
then
    avg_ms_f=$(($avg_ms_f / $n_f))
    avg="(average of "$avg_ms_f" meal(s) passed)"
else
    avg=""
fi
echo -e "\e"$fail_color"fail: "$n_f" "$avg"\e[0m"
echo -e "\e"$success_color"success: "$n_s"\e[0m"
echo
fi


#######################################################
#                                                     #
#                      Test 3                         #
#                                                     #
#######################################################
x=0
t3_show_output=1
[ $show_output == "0" ] && t3_show_output=0

if (($specific == 0 || ($specific > 0 && $specific == 3)));
then
echo
echo -e "\e[1;33mTest 3 - One philosopher should die:\e[0m"
echo
n_s=0
n_f=0
avg_ms_f=0
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
        start_color="$fail_color"
        t_res="FAIL (died "$(($n2 - $diff))"ms more than necessary)"
        n_f=$(($n_f + 1))
        avg_ms_f=$(($avg_ms_f + $(($n2 - $diff))))
    else
        start_color="$success_color"
        t_res="SUCCESS (died "$(($diff - $n2))"ms after previous action)"
        n_s=$(($n_s + 1))
    fi
    echo -e "\e$start_color$(($x + 1))) ./philo $params "$t_res"\e[0m"
    [ $t3_show_output != "0" ] && echo "$output"
    sleep $time
    #valgrind --leak-check=full $exec $params
    #sleep $time
    x=$(($x + 1))
done

# calc average ms failed
echo -e "\e"$test_result_color"Test 3 - Tested "$repeat" time(s) - Result:\e[0m"
if test $avg_ms_f != 0; 
then
    avg_ms_f=$(($avg_ms_f / $n_f))
    avg="(average of "$avg_ms_f"ms passed)"
else
    avg=""
fi
echo -e "\e"$fail_color"fail: "$n_f" "$avg"\e[0m"
echo -e "\e"$success_color"success: "$n_s"\e[0m"
echo
fi

#######################################################
#                                                     #
#                      Test 4                         #
#                                                     #
#######################################################
x=0
t4_show_output=1
[ $show_output == "0" ] && t4_show_output=0
[ $max_meals_by_philo -eq "0" ] && max_meals_by_philo=""

if (($specific == 0 || ($specific > 0 && $specific == 4)));
then
echo
echo -e "\e[1;33mTest 4 - No philosopher should die:\e[0m"
echo
n_s=0
n_f=0
avg_ms_f=0
while [ $x -le $(($repeat - 1)) ]
do
    params="4 410 200 200 $max_meals_by_philo"
    # calc diff between last and before last time is bigger than 10ms
    output=$($exec $params)
    death=$(echo "$output" | grep died | wc -l)
    if (($death > 0))
    then
        start_color="$fail_color"
        t_res="FAIL (after a simulation of $max_meals_by_philo meal(s) by philosophers, the someone died, probably your program need to be optimed)"
        n_f=$(($n_f + 1))
        avg_ms_f=$(($avg_ms_f + $(($n2 - $diff))))
    fi
    if (($death == 0))
    then
        start_color="$success_color"
        t_res="SUCCESS (after a simulation of $max_meals_by_philo meal(s) by philosophers, no one died, probably your app is on the right way, now do tests without max_meals_by_philo"
        n_s=$(($n_s + 1))
    fi
    echo -e "\e$start_color$(($x + 1))) ./philo $params "$t_res"\e[0m"
    [ $t4_show_output != "0" ] && echo "$output"
    sleep $time
    #valgrind --leak-check=full $exec $params
    #sleep $time
    x=$(($x + 1))
done
echo
# calc average ms failed
echo -e "\e"$test_result_color"Test 4 - Tested "$repeat" time(s) - max meals by philosopher defined to $max_meals_by_philo meal(s) by philosopher - Result:\e[0m"
echo
echo -e "\e"$fail_color"fail: "$n_f"\e[0m"
echo -e "\e"$success_color"success: "$n_s"\e[0m"
echo
fi


#######################################################
#                                                     #
#                      Test 5                         #
#                                                     #
#######################################################
x=0
t5_show_output=1
[ $show_output == "0" ] && t5_show_output=0
[ $max_meals_by_philo == "0" ] && max_meals_by_philo=""

if (($specific == 0 || ($specific > 0 && $specific == 5)));
then
echo
echo -e "\e[1;33mTest 5 - No philosopher should die:\e[0m"
echo
n_s=0
n_f=0
avg_ms_f=0
while [ $x -le $(($repeat - 1)) ]
do
    params="5 800 200 200 $max_meals_by_philo"
    # calc diff between last and before last time is bigger than 10ms
    output=$($exec $params)
    death=$(echo "$output" | grep died | wc -l)
    if (($death > 0))
    then
        start_color="$fail_color"
        t_res="FAIL (after a simulation of $max_meals_by_philo meal(s) by philosophers, the someone died, probably your program need to be optimed)"
        n_f=$(($n_f + 1))
        avg_ms_f=$(($avg_ms_f + $(($n2 - $diff))))
    fi
    if (($death == 0))
    then
        start_color="$success_color"
        t_res="SUCCESS (after a simulation of $max_meals_by_philo meal(s) by philosophers, no one died, probably your app is on the right way, now do tests without max_meals_by_philo"
        n_s=$(($n_s + 1))
    fi
    echo -e "\e$start_color$(($x + 1))) ./philo $params "$t_res"\e[0m"
    [ $t5_show_output != "0" ] && echo "$output"
    sleep $time
    #valgrind --leak-check=full $exec $params
    #sleep $time
    x=$(($x + 1))
done
echo
# calc average ms failed
echo -e "\e"$test_result_color"Test 5 - Tested "$repeat" time(s) - max meals by philosopher defined to $max_meals_by_philo meal(s) by philosopher - Result:\e[0m"
echo
echo -e "\e"$fail_color"fail: "$n_f"\e[0m"
echo -e "\e"$success_color"success: "$n_s"\e[0m"
echo
fi