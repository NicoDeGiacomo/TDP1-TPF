#ifndef POSITION_H_
#define POSITION_H_

class Position {
  int x_;
  int y_;

 private:
  void validate_position() const;

 public:
  Position(int x, int y);

  int getX() const;

  int getY() const;

  Position operator+(const Position& pos2) const;
};

#endif  // POSITION_H_
