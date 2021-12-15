use std::cell::RefCell;

struct Test {
  x: u32
}

impl Drop for Test {
  fn drop(&mut self) {
    println!("Dropping!");
  }
}

thread_local!(static FOO: RefCell<Test> = RefCell::new(Test { x: 1 }));

#[no_mangle]
pub extern "C" fn test() {
  FOO.with(|f| {
    println!("in main {}", f.borrow().x);
    f.borrow_mut().x = 2;
  });
}
