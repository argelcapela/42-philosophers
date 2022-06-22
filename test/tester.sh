# 
# Copyright © 2022 de Argel Capela, Todos os direitos reservados
#

# banner
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
time=0.1

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


# let's start test
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

x=0
repeat=2
if ((specific == 0 || (specific > 0 && specific == 3)));
then
echo
echo -e "\e[0;33mTest 3 - One philosopher should die:\e[0m"
echo
while [ $x -le $(($repeat - 1)) ]
do
    echo -e "\e[1;32m$(($x + 1))) ./philo 4 310 200 100\e[0m"
    echo
    $exec 4 310 200 100
    echo
    valgrind --leak-check=full $exec 4 310 200 100
    sleep $time
    x=$(($x + 1))
    echo
    echo
done
echo
echo
fi

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

    echo -e
    sleep $time
    x=$(($x + 1))
done
echo
echo
fi

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
