#include <iostream>
#include <queue>
#include <map>
using namespace std;


struct reservation_t {
  const long time;
  const string hotel_name;
  const int client_id;
  const int room_count;
};


class HotelReservationManager {
public:
  void Book(const reservation_t& r) {
    reservations_.push(r);
    rooms_[r.hotel_name] += r.room_count;
    clients_[r.hotel_name][r.client_id] += r.room_count;
    Adjust(r.time);
  }

  int Clients(const string& hotel_name) const {
    if (clients_.count(hotel_name) == 0) {
      return 0;
    }
    return clients_.at(hotel_name).size();
  }

  int Rooms(const string& hotel_name) const {
    if (rooms_.count(hotel_name) == 0) {
      return 0;
    }
    return rooms_.at(hotel_name);
  }

private:
  queue<reservation_t> reservations_;
  map<string, int> rooms_;
  map<string , map<int, int>> clients_;

  void Adjust(long current_time) {
    while (!reservations_.empty() && current_time - reservations_.front().time >= 86400) {
      const reservation_t& r = reservations_.front();
      rooms_[r.hotel_name] -= r.room_count;
      if (clients_[r.hotel_name][r.client_id] == r.room_count) {
        clients_[r.hotel_name].erase(r.client_id);
      } else {
        clients_[r.hotel_name][r.client_id] -= r.room_count;
      }
      reservations_.pop();
    }
  }
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int q;
  cin >> q;
  HotelReservationManager manager;
  string command;
  for (int i = 0; i < q; ++i) {
    cin >> command;
    if (command == "BOOK") {
      long time;
      string hotel_name;
      int client_id, room_count;
      cin >> time >> hotel_name >> client_id >> room_count;
      manager.Book({time, hotel_name, client_id, room_count});

    } else if (command == "CLIENTS") {
      string hotel_name;
      cin >> hotel_name;
      cout << manager.Clients(hotel_name) << '\n';

    } else if (command == "ROOMS") {
      string hotel_name;
      cin >> hotel_name;
      cout << manager.Rooms(hotel_name) << '\n';

    }
  }
  return 0;
}
