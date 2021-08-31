#pragma once
#include <iostream>
#include <type_traits>

struct Node {
	size_t id; //item descriptor, store its value in array in kd_tree
	Node* left = nullptr;
	Node* right = nullptr;
	
	Node(size_t in_id) : id(in_id) {}

};

#define abstract
template <typename T>
abstract class PointType {
	T get_x();
	T get_y();
	T get_z();
	void print() const;
};

template <typename T, int N>
struct PointN : PointType<T>{
	T point_data[N];

	T get_x() const { return point_data[0]; }
	T get_y() const { return point_data[1]; }
	T get_z() const { return point_data[2]; }
	T get_i(int i) const {
		if (i > N)
			return get_i[0];//throw?
		return point_data[i];
	}
};

class BasicPoint : PointType<int> {
	int x;
	int y;
	int z;
public:
	void set_x(const int& x_in) { x = x_in; }
	void set_y(const int& y_in) { y = y_in; }
	void set_z(const int& z_in) { z = z_in; }
	int get_x() const { return x; }
	int get_y() const { return y; }
	int get_z() const { return z; }
	void print() const { std::cout << get_x() << " " << get_y() << " " << get_z() << "\n"; }
	//friend std::ostream& operator << (std::ostream& os, const BasicPoint& p);
};


//std::ostream& operator << (std::ostream& os, const BasicPoint& p) {
//	os << p.get_x() << " " << p.get_y() << " " << p.get_z() << "\n";
//	return os;
//}


template <typename PointT, typename CoordinatT> 
//requires(PointType pt, int pt) std::is_base_of<PointType, PointT>
class kd_tree
{
private:
	Node* root = nullptr;
	PointT* cloud;//some struct to represent cloud of points
	size_t length = -1;
public:
	kd_tree() = delete;

	kd_tree(PointT* cloud_in, size_t len)
	{
		cloud = new PointT[len];
		cloud = cloud_in;
		length = len;
		static_assert(std::is_base_of<PointType<CoordinatT>, PointT>::value, "in kd_tree PointT is not PointType");
	}

	void insert_helper(Node* current_root, size_t point_id, size_t depth) {
		if (current_root == nullptr) {
			current_root = new Node(point_id);
			std::cout << "insert to " << depth << "\n";
		}
		else {
			size_t dimension = depth % 3;
			if (dimension == 0) {
				if (cloud[point_id].get_x() < cloud[current_root->id].get_x()) {
					insert_helper(current_root->left, point_id, depth + 1);
				}
				else {
					insert_helper(current_root->right, point_id, depth + 1);
				}
			}
			else if (dimension = 1) {
				if (cloud[point_id].get_y() < cloud[current_root->id].get_y()) {
					insert_helper(current_root->left, point_id, depth + 1);
				}
				else {
					insert_helper(current_root->right, point_id, depth + 1);
				}
			}

			else if (dimension = 2) {
				if (cloud[point_id].get_z() < cloud[current_root->id].get_z()) {
					insert_helper(current_root->left, point_id, depth + 1);
				}
				else {
					insert_helper(current_root->right, point_id, depth + 1);
				}
			}
		}
	}

	void insert(size_t point_id) {
		insert_helper(root, point_id, 0);
	}
	
	void print() const {
		for (int i = 0; i < length; ++i) {
			//std::cout << cloud[i] << "\n";
			cloud[i].print();
		}
	}

};

