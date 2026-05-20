#!/bin/bash

BIN_ORIG="nm"
BIN_MINE="./ft_nm"

OPTIONS=(
# Toutes les combinaisons d’options
    "" "-a" "-g" "-u" "-r" "-p"
    "-ag" "-au" "-ar" "-ap" "-gu" "-gr" "-gp" "-ur" "-up" "-rp"
    "-agu" "-agr" "-agp" "-aur" "-aup" "-arp" "-gur" "-gup" "-grp" "-urp"
    "-agru" "-agrp" "-agup" "-aurp" "-gurp"
    "-aurgp"
)

run_test() {
    FILE="$1"
    OPTS="$2"

    echo -e "\n=== Test: $FILE $OPTS ==="
    $BIN_ORIG $FILE $OPTS > a2
    $BIN_MINE $FILE $OPTS > a1
    diff --color=always a1 a2
    if [ $? -ne 0 ]; then
        echo "Diff detected for: $FILE $OPTS"
        exit 1
    else
        echo "OK"
    fi
}

if [ $# -lt 1 ]; then
    FILE="a.out"
    for OPT in "${OPTIONS[@]}"; do
        run_test "$FILE" "$OPT"
    done
    echo -e "\n Tous les tests sont passés avec succès !"
    rm -f a1 a2
    exit 1
fi

for FILE in "$@"; do
    echo -e "\n================================================="
    echo "      Tests pour $FILE"
    echo "================================================="

    for OPT in "${OPTIONS[@]}"; do
        run_test "$FILE" "$OPT"
    done
done

echo -e "\n Tous les tests sont passés avec succès !"
rm -f a1 a2