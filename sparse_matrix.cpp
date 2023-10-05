#include <iostream>
#include <cassert>
using namespace std;

struct ArrayNode {
	int data;
	int idx;
	ArrayNode* next;
	ArrayNode* prev;

	ArrayNode(int data, int idx) : data(data), idx(idx), next(nullptr), prev(nullptr) { }
};

class ArrayLinkedList {
private:
	ArrayNode* head;
	ArrayNode* tail;
	int array_length; // user length (maximum capacity we have)
    int actual_size; // number of nodes

    void link(ArrayNode* first, ArrayNode* second) {//I didn't put if conditions for asserting that first or second pointers are NULL or not 
                                            // before accessing them as I'm sure that they won't be NULL because of the dummy head and tail
        first->next = second;
        second->prev = first;
    }

    // if there is an item in our linked list with the "idx" parameter, "insert_sorted" function will modify its value with the 
    // "value" parameter if "add_if_exist" is false. Otherwise, it will increment the old value with the new one.
    void insert_sorted(int value, int idx, bool add_if_exist = false) { // sorting is based on the indices, not values
        bool is_inserted = false;
        for (ArrayNode* cur = head->next; cur->next; cur = cur->next) { // starts after dummy head and stops before dummy tail
            if (idx < cur->idx) {
                ArrayNode* new_node = new ArrayNode(value, idx);
                ArrayNode* previous = cur->prev;
                link(previous, new_node);
                link(new_node, cur);
                actual_size++;
                is_inserted = true;
                break;
            }
            else if (idx == cur->idx) {
                if (add_if_exist)
                    cur->data += value;
                else
                    cur->data = value;
                is_inserted = true;
                break;
            }
        }
        if (!is_inserted) { // "idx" parameter is greater than all indices in our linked list **OR** there isn't any real element in our linked list 
            ArrayNode* new_node = new ArrayNode(value, idx);
            ArrayNode* previous = tail->prev;
            link(previous, new_node);
            link(new_node, tail);
        }
    }

public:
	ArrayLinkedList(int array_length) :
            head(nullptr), tail(nullptr), array_length(array_length), actual_size(2) {
        // Dummy nodes of index: -1 and INT_MAX to make coding shorter and more robust! (assuming that all real indices will be < INT_MAX)
        // https://en.wikipedia.org/wiki/Sentinel_node
        head = new ArrayNode(0, -1);
        tail = new ArrayNode(0, INT_MAX);
        link(head, tail);
    }

	void set_value(int value, int idx, bool add_if_exist = false) {
		assert(0 <= idx && idx < array_length);
        insert_sorted(value, idx, add_if_exist);
	}

    int get_value(int idx) const {
		assert(0 <= idx && idx < array_length);
        for (ArrayNode* cur = head->next; cur->next; cur = cur->next) // starts after dummy head and stops before dummy tail
            if (cur->idx == idx)
                return cur->data;
        return 0; // Not Found
    }

    void add_array(const ArrayLinkedList& arr) {
        assert(arr.array_length == array_length);
        for (ArrayNode* cur = arr.head->next; cur->next; cur = cur->next) // starts after dummy head and stops before dummy tail
            insert_sorted(cur->data, cur->idx, true);
    }

    void print() const {
        ArrayNode* cur = head->next; // starts after dummy head 
        for (int idx = 0; idx < array_length; idx++) {
            if (cur && cur->idx == idx) {
                cout << cur->data << " ";
                cur = cur->next;
            }
            else
                cout << "0 ";
        }
        cout << "\n";
    }

    void print_nonzero() const {
        for (ArrayNode* cur = head->next; cur->next; cur = cur->next) // starts after dummy head and stops before dummy tail
            cout << cur->data << " ";
        cout << "\n";
    }

    ArrayNode* getHead() const {
        return head;
    }
};

struct RowNode {
	ArrayLinkedList data;
	int row_idx;
	RowNode* next;
	RowNode* prev;

	RowNode(int row, int cols) : data(cols), row_idx(row), next(nullptr), prev(nullptr) { }
};

class SparseMatrix {
private:
	RowNode* head;
	RowNode* tail;
	int matrix_rows; // user rows (maximum capacity of rows we have)
	int matrix_cols; // user cols (maximum capacity of cols we have)
    int actual_rows; // number of linked lists (num of rows)

    void link(RowNode* first, RowNode* second) {//I didn't put if conditions for asserting that first or second pointers are NULL or not 
                                            // before accessing them as I'm sure that they won't be NULL because of the dummy head and tail
        first->next = second;
        second->prev = first;
    }

    // if there is a row in our matrix with the "row" parameter, "insert_sorted" function will modify its value with the 
    // "value" parameter if "add_if_exist" is false. Otherwise, it will increment the old value with the new one.
    void insert_sorted(int value, int row, int col, bool add_if_exist = false) { // sorted based on row indices
        bool is_inserted = false;
        for (RowNode* cur = head->next; cur->next; cur = cur->next) { // starts after dummy head and stops before dummy tail
            if (row < cur->row_idx) {
                RowNode* new_row = new RowNode(row, matrix_cols);
                RowNode* previous = cur->prev;
                link(previous, new_row);
                link(new_row, cur);
                new_row->data.set_value(value, col, add_if_exist);
                actual_rows++;
                is_inserted = true;
                break;
            }
            else if (row == cur->row_idx) {
                cur->data.set_value(value, col, add_if_exist);
                is_inserted = true;
                break;
            }
        }
        if (!is_inserted) { // "row" parameter is greater than all row indices in our matrix **OR** there isn't any real row in our matrix 
            RowNode* new_row = new RowNode(row, matrix_cols);
            RowNode* previous = tail->prev;
            link(previous, new_row);
            link(new_row, tail);
            new_row->data.set_value(value, col, add_if_exist);
            actual_rows++;
        }
    }

public:
	SparseMatrix(int rows, int cols) : matrix_rows(rows), matrix_cols(cols) {
        // Dummy nodes of row index: -1 and INT_MAX to make coding shorter and more robust! (assuming that all real row indices will be < INT_MAX)
        // https://en.wikipedia.org/wiki/Sentinel_node
        head = new RowNode(-1, matrix_cols);
        tail = new RowNode(INT_MAX, matrix_cols);
        link(head, tail);
    }

	void set_value(int value, int row, int col) {
		assert(0 <= row && row < matrix_rows && 0 <= col && col < matrix_cols);
        insert_sorted(value, row, col);
	}

    int get_value(int row, int col) const {
		assert(0 <= row && row < matrix_rows && 0 <= col && col < matrix_cols);
        for (RowNode* cur = head->next; cur->next; cur = cur->next) // starts after dummy head and stops before dummy tail
            if (cur->row_idx == row)
                return cur->data.get_value(col);
        return 0; // Not Found
    }

    void add_matrix(const SparseMatrix& matrix) { // very slow :( => O(n^2 * m^2) time, where n is rows and m is columns
        assert(matrix.matrix_rows == matrix_rows && matrix.matrix_cols == matrix_cols);
        for (RowNode* cur_list = matrix.head->next; cur_list->next; cur_list = cur_list->next)// starts after dummy head and stops before dummy tail
            for (ArrayNode* cur_node = cur_list->data.getHead()->next; cur_node->next; cur_node = cur_node->next)
                insert_sorted(cur_node->data, cur_list->row_idx, cur_node->idx, true);
    }

    void print() const {
        cout << "Print Matrix: " << matrix_rows << " X " << matrix_cols << "\n\n";
        RowNode* cur = head->next; // starts after dummy head 
        for (int row = 0; row < matrix_rows; row++) {
            if (cur && cur->row_idx == row) {
                cur->data.print();
                cur = cur->next;
            }
            else {
                for (int col = 0; col < matrix_cols; col++)
                    cout << "0 ";
                cout << "\n";
            }
        }
        cout << "\n";
    }

    void print_nonzero() const {
        cout << "Print Matrix: " << matrix_rows << " X " << matrix_cols << "\n\n";
        for (RowNode* cur = head->next; cur->next; cur = cur->next) // starts after dummy head and stops before dummy tail
            cur->data.print_nonzero();
        cout << "\n";
    }
};

int main() {
	SparseMatrix mat(10, 10);
	mat.set_value(5, 3, 5);
	mat.set_value(7, 3, 7);
	mat.set_value(2, 3, 2);
	mat.set_value(0, 3, 2); // modify the above line
	mat.set_value(6, 5, 6);
	mat.set_value(4, 5, 4);
	mat.set_value(3, 7, 3);
	mat.set_value(1, 7, 1);
	//mat.set_value(1, 70, 1);
	mat.print();
	mat.print_nonzero();

	SparseMatrix mat2(10, 10);
	mat2.set_value(5, 1, 9);
	mat2.set_value(6, 3, 8);
	mat2.set_value(9, 9, 9);
	mat.add_matrix(mat2);
	mat.print_nonzero();

    cout << mat.get_value(1, 9) << "\n";
    cout << mat.get_value(3, 5) << "\n";
    cout << mat.get_value(7, 7) << "\n";

	return 0;
}
