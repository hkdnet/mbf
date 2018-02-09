@vec = internal global [30000 x i32] zeroinitializer, align 4

define i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 65, i32* %1, align 4
  %2 = load i32, i32* %1, align 4
  call i32 @putchar(i32 %2)
  ret i32 0
}

declare i32 @putchar(i32) #2
