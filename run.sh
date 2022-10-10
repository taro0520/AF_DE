TOKEN="bcvFUqU3gDZmibaQGWumXmH5NEQJPlOwj92HAqtJ38X"
# message=$(./main de 50 100 30 500 0.5 0.5)
# curl https://notify-api.line.me/api/notify -H "Authorization: Bearer ${TOKEN}" -F "message=${message}"
# message=$(./main de 50 100 30 2000 0.5 0.5)
# curl https://notify-api.line.me/api/notify -H "Authorization: Bearer ${TOKEN}" -F "message=${message}"
counter=1
while [ $counter -le 10 ]; do
message=$(./main de 50 100 30 2000 0.5 0.5)
curl https://notify-api.line.me/api/notify -H "Authorization: Bearer ${TOKEN}" -F "message=${message}"
done