# > ポインタをインクリメントする。ポインタをptrとすると、C言語の「ptr++;」に相当する。
# < ポインタをデクリメントする。C言語の「ptr--;」に相当。
# + ポインタが指す値をインクリメントする。C言語の「(*ptr)++;」に相当。
# - ポインタが指す値をデクリメントする。C言語の「(*ptr)--;」に相当。
# . ポインタが指す値を出力に書き出す。C言語の「putchar(*ptr);」に相当。
# , 入力から1バイト読み込んで、ポインタが指す先に代入する。C言語の「*ptr=getchar();」に相当。
# [ ポインタが指す値が0なら、対応する ] の直後にジャンプする。C言語の「while(*ptr){」に相当。
# ] ポインタが指す値が0でないなら、対応する [ （の直後[1]）にジャンプする。C言語の「}」に相当[2]。

class Bf
  def initialize(input, out: $stdout, debug: false)
    @input = input.freeze
    @out = out
    @debug = debug
    @cur = 0
    @bytes = Array.new(30_000) { 0 }
  end

  def process
    idx = 0

    until idx >= @input.size
      idx = _process(idx)
    end
  end

  def _process(idx)
    case @input[idx]
    when  '>' then @cur += 1
    when  '<' then @cur -= 1
    when  '+' then @bytes[@cur] += 1
    when  '-' then @bytes[@cur] -= 1
    when  '.' then @out.putc @bytes[@cur]
    when  ',' then @bytes[@cur] = getc
    when  '[' # ポインタが指す値が0なら、対応する ] の直後にジャンプする。C言語の「while(*ptr){」に相当。
      raise 'NotImplemented'
    when  ']' # ポインタが指す値が0でないなら、対応する [ （の直後[1]）にジャンプする。C言語の「}」に相当[2]。
      raise 'NotImplemented'
    end
    idx + 1
  end
end
