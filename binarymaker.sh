#!/bin/bash

ip_to_binary() {
    local IFS='.'
    read -r -a octets <<< "$1"
    local binary_ip=""
    for octet in "${octets[@]}"; do
        binary_octet=$(echo "obase=2; $octet" | bc)
        binary_octet=$(printf "%08d" "$binary_octet")
        binary_ip="$binary_ip$binary_octet"
    done
    echo "$binary_ip"
}

IP=$(ip_to_binary $1)
MASK=$(ip_to_binary $2)

echo -e "$IP : IP\n$MASK : MASK"