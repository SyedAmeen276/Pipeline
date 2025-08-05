#!/bin/bash

rm -f *.json

files=("input.txt" "input1.txt" "input2.txt")

sensors=("sensorA" "sensorB" "sensorC" "sensorD")
locations=("basement" "rooftop")

for i in {1..100}
do
  evt_id="evt$((RANDOM % 9000 + 1000))"
  temperature=$(awk -v min=20 -v max=40 'BEGIN{srand(); printf "%.1f", min+rand()*(max-min)}')
  humidity=$((RANDOM % 31 + 50))
  source=${sensors[$RANDOM % ${#sensors[@]}]}
  location=${locations[$RANDOM % ${#locations[@]}]}
  priority=$((RANDOM % 4 + 2))
  batch=$((RANDOM % 100 + 1))

  output_file=${files[$RANDOM % ${#files[@]}]}

  # Create JSON
  json=$(cat <<EOF
{
  "event_id": "$evt_id",
  "payload": {
    "temperature": $temperature,
    "humidity": $humidity,
    "status": "OK",
    "tags": ["sensor", "indoor"]
  },
  "source": "$source",
  "type": "temperature",
  "metadata": {
    "location": "$location",
    "batch": $batch,
    "priority": $priority
  }
}
EOF
)

  echo "$json" >> "$output_file"
done
