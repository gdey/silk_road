#!/usr/bin/perl
use v5.12;
use Data::Dumper;

sub gen_array {

   my $length = shift;
   my $l = $length - 1;
   my $s = scalar @_;
   my @a = ();
   my @n = 0 .. $l;
   if ( $s < $l ){
     for ( grep { $_ != $s } @n ){
       #say "-"x$l."-> calling self($length,".join(",",@_).",$_)";
       push @a, gen_array($length,@_,$_)
     }
   } else {
     
     for my $i ( 0 .. ($l-1) ){
       my @b = (@_,$i); 
       my $b = 0;
       my @c = map{ 
          #say '-'x$l.'->['.join(',',@b).'] b[$_]:'.$b[$_]." \$_:$_ == ".$b[$b[$_]];
          $b[$b[$_]] == $_ 
       } @n ;
       $b += $_ for( @c );
       if( $b == $length ) {
         #say 'pushing: $b == $length ['.join(',',@b).']'.Dumper(\@c);
         push @a, \@b;
       }
     }
   }
   #say "Returning: ".Dumper(\@a);
   return @a;

}

sub hex_number_str { '0x'.join('',reverse(@_)) };

sub rotate90 {
  my %r90 = (
      4 => [3,0,1,2],
      8 => [2,3,7,6,1,0,4,5]
  );
  my $s = scalar @_;
  say "S is $s ";
  my @n = ();
  for my $i ( 0 .. ($s-1) ){
    say "i: $i ->".$r90{$s}->[$i]." d: ".$_[$i]." ->".$r90{$s}->[$_[$i]];

  $n[ $r90{$s}->[$i] ] = $r90{$s}->[$_[ $i ]] for 0..$s;
  }
  return @n;
}

sub references {
    my %r =  map { $_->{reference} => 1 } @_;
    return sort{ $a <=> $b } keys %r;
}

sub foo {
   my %h_t = ();
   my $ci = 1;

   for my $tile ( @_ ){
     
     my @ttiles = ( $tile );
     my @keys  = ( hex_number_str(@$tile) );
     next if exists $h_t{$keys[0]}; # It's already built up, skip it.

     for my $rt ( 1 .. 3 ){
        my $tiles = $ttiles[$rt-1];
        
        say Dumper($tiles);
        my @my_tiles = rotate90(@$tiles);
        $ttiles[$rt] = \@my_tiles;
        $keys[$rt]   = hex_number_str(@my_tiles);
     }
     my $ref = $ci;
     for my $i ( 0 .. 3 ){
        next if exists $h_t{$keys[$i]};
        $h_t{$keys[$i]} = {
            raw => $ttiles[$i],
            name => $keys[$i],
            index => $ci++, # assign then increment.
            reference => $ref,
             90 => $keys[(($i + 1) % 4)],
            180 => $keys[(($i + 2) % 4)],
            270 => $keys[(($i + 3) % 4)],
        }
     }
   }
   say "zero";
   my @tzero = (0..(scalar(@{$_[0]})-1));
   my $kzero = hex_number_str(@tzero);
   my $zero = {
      raw => \@tzero,
      index => 0,
      name => $kzero,
      reference => 0,
       90 => $kzero,
      '90i' => 0,
      180 => $kzero,
      '180i' => 0,
      270 => $kzero,
      '270i' => 0,
      'ref' => sprintf('0x'.'%02x'x4,0,0,0,0)
   };
   say 'done zero';
   for my $key ( keys %h_t ){
      my $h = $h_t{$key};
      $h->{'90i'} = $h_t{ $h->{90} }->{index};
      $h->{'180i'} = $h_t{ $h->{180} }->{index};
      $h->{'270i'} = $h_t{ $h->{270} }->{index};
      $h->{'ref'}  = sprintf('0x'.'%02x'x4,$h->{'270i'},$h->{'180i'},$h->{'90i'},$h->{reference});
   }
   return [ $zero, sort { $a->{index} <=> $b->{index} } values %h_t ];
}

my $var_name = $ARGV[0] || die "Need a var name";
my $count = $ARGV[1] || 4;
my @f = gen_array($count);
use Data::Dumper;
my $tiles = foo(@f);
say Dumper( $tiles );
my @refs = references( @$tiles );
say Dumper( \@refs , scalar @refs );
#  perl -E 'printf("0x%02x%02x%02x\n",155,7,105)'
#say "// Generated using: $0 $var_name $count";
#say "const tile_maps_type ${var_name}\[][] = {";
#say '//DDLLRRUU';
#say '//'.join('',reverse((0..($count-1))));
#say join( ",\n", map { hex_number_str( @$_ ) } @f); 
#
#say;
#say join( ",\n", map { hex_number_str(@$_) =>  hex_number_str( rotate90(@$_) ) } @f); 
#
#say '};'
