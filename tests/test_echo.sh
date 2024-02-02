# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_echo.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/02 17:59:49 by fmontser          #+#    #+#              #
#    Updated: 2024/02/02 18:46:27 by fmontser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#TODO more tests!

OK="\033[0;32m[OK]\033[0m"
KO="\033[0;31m[KO]\033[0m"

BIN_PATH="./../bin/echo"
TOTAL_KO=0
TEST_N=0

TEST_LIST=(
	"test"
	"multi args test"
	'quoted test'
	""multi" "args" "quoted" "test""
	"new line'\n'test"
	""
	"$?"
)

compare()
{
	echo
	echo	TEST Nº $TEST_N
	echo		$1 > temp1.tmp
	$BIN_PATH	$1 > temp2.tmp

	if diff temp1.tmp temp2.tmp &> /dev/null; then
		echo $OK
	else
		((TOTAL_KO++))
		echo $KO
	fi
		cat -e temp1.tmp
		cat -e temp2.tmp
		rm -f *.tmp
		((TEST_N++))
}

for test in "${TEST_LIST[@]}"; do
	compare "$test"
done

KO_SUMMARY="\033[0;31m$TOTAL_KO of $TEST_N FAILED\033[0m"
PASS_SUMMARY="\033[0;32mPASSED ALL TESTS!\033[0m"
echo
if [[ $TOTAL_KO -gt 0 ]]; then
	echo $KO_SUMMARY
else
	echo $PASS_SUMMARY
fi
