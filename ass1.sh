# Write a program to implement an address book with options given below: 
# a) Create address book. 
# b) View address book. 
# c) Insert a record. 
# d) Delete a record. 
# e) Modify a record. 
# f) Exit


address_book="address_book.txt"

if [ ! -e "$address_book" ]; then
    touch "$address_book"
fi

function print_menu {
    echo "Address Book Menu:"
    echo "1) View address book"
    echo "2) Insert a record"
    echo "3) Delete a record"
    echo "4) Modify a record"
    echo "5) Search for a record"
    echo "6) Exit"
}

function view_address_book {
    if [ -s "$address_book" ]; then
        cat "$address_book"
    else
        echo "No records found in the address book."
    fi
}

function insert_record {
    read -p "Enter student roll number: " roll_number
    read -p "Enter student class: " student_class
    read -p "Enter student name: " name
    read -p "Enter student address: " address
    echo "Roll Number: $roll_number, Class: $student_class, Name: $name, Address: $address" >> "$address_book"
    echo "Record inserted."
}

function delete_record {
    if [ -s "$address_book" ]; then
        read -p "Enter student roll number to delete: " roll_number
        if grep -q "Roll Number: $roll_number" "$address_book"; then
            grep -v "^Roll Number: $roll_number" "$address_book" > "$address_book.tmp"
            mv "$address_book.tmp" "$address_book"
            echo "Record deleted."
        else
            echo "Record not found in the address book."
        fi
    else
        echo "No records found in the address book."
    fi
}

function modify_record {
    if [ -s "$address_book" ]; then
        read -p "Enter student roll number to modify: " roll_number
        if grep -q "Roll Number: $roll_number" "$address_book"; then
            read -p "Enter new student class: " new_student_class
            read -p "Enter new student name: " new_name
            read -p "Enter new student address: " new_address
            awk -v roll_number="$roll_number" -v new_student_class="$new_student_class" -v new_name="$new_name" -v new_address="$new_address" -F, '$1 == "Roll Number: " roll_number {$2=" Class: " new_student_class; $3=" Name: " new_name; $4=" Address: " new_address} {print}' "$address_book" > "$address_book.tmp"
            mv "$address_book.tmp" "$address_book"
            echo "Record modified."
        else
            echo "Record not found in the address book."
        fi
    else
        echo "No records found in the address book."
    fi
}

function search_record {
    if [ -s "$address_book" ]; then
        read -p "Enter student roll number or class to search: " search_term
        if grep -i "Roll Number: $search_term\|Class: $search_term" "$address_book"; then
            echo "Search complete."
        else
            echo "No records found matching the search term."
        fi
    else 
        echo "No records found in the address book."
    fi
}

while :
do
    print_menu
    read -p "Enter your choice: " choice

    case "$choice" in
        1)
            view_address_book
            ;;
        2)
            insert_record
            ;;
        3)
            delete_record
            ;;
        4)
            modify_record
            ;;
        5)
            search_record
            ;;
        6)
            echo "Exiting the address book."
            exit 0
            ;;
        *)
            echo "Invalid choice. Please try again."
            ;;
    esac
done


