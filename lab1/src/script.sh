#!/bin/bash

# $RANDOM возвращает различные случайные числа при каждом обращении к ней.
# Диапазон изменения: 0 - 32767 (16-битовое целое со знаком).

MAXCOUNT=150
count=1

echo
echo "$MAXCOUNT случайных чисел:"
echo "-----------------"
while [ "$count" -le $MAXCOUNT ]      # Генерация 10 ($MAXCOUNT) случайных чисел.
do
  number=$sudo < /dev/random tr -dc 0-9 | head -c2
  echo $number
  let "count += 1"  # Нарастить счетчик.
done
echo "-----------------"
