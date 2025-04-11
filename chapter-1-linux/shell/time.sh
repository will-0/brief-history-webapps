echo "Long real time, short user/sys time"
time sleep 1
echo "Active processes"
time bash -c 'for i in {1..100000}; do :; done'