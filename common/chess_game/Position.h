#ifndef POSITION_H_
#define POSITION_H_

class Position {
  unsigned short x_;
  unsigned short y_;

 private:
  void validate_position() const;

 public:
  Position(unsigned short x, unsigned short y);

  unsigned short getX() const;

  unsigned short getY() const;
};

#endif  // POSITION_H_
