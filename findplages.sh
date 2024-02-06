#!/bin/bash

binary_to_ip() {
    local binary_ip="$1"
    local ip=""
    local octet=""
    for ((i = 0; i < ${#binary_ip}; i += 8)); do
        octet="${binary_ip:$i:8}"
        decimal_octet=$(echo "ibase=2; $octet" | bc)
        ip="$ip$decimal_octet."
    done
    echo "${ip%.*}"
}

IP=$(binary_to_ip $1)

echo -e "$IP : IP"