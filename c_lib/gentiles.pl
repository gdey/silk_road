#!/usr/bin/perl
use v5.12;
use Data::Dumper;

sub combine {
   my $v = shift;
   my $cval = sub {
      return [ $_[1] ] unless defined $_[0];
      return [ grep( { defined } @{$_[0]}),$_[1] ] if ref($_[0]) eq 'ARRAY';
      return [ $_[0],$_[1] ]
   };
   map { $cval->($v,$_) } @_;
}

sub prems_ {
   my ($idxs,@vals) = @_;
   my $s= scalar @vals;
   my $idx = $idxs->[ -1 ];
   my $nlidx = $s-2;
   my $lidx = $s-1;
   my @rvals = ();
   return () unless defined $idx;
   for my $idx1 ( ($idx+1)..$nlidx){
      push @rvals, combine( [ @vals[@$idxs,$idx1] ], @vals[($idx1+1)..$lidx] );
   }
   return @rvals;
}

sub prems {
   
   my @vals = @_;
   my $s= scalar @_;
   my @rvals = ();
   my $nlidx = $s-2;
   my $lidx = $s-1;
   for my $idx ( undef, 0..$nlidx ){
      my $i = defined $idx? $idx+1 : 0;
      push @rvals, combine( [ defined $idx? $vals[$idx] : undef ],@vals[$i..$lidx] );
      for my $idxX ( $idx..$nlidx ){
         push @rvals, prems_([$idx..$idxX],@vals);
      }
      #if( defined $idx ){
      #   for my $idx1 ( ($idx+1)..$nlidx ){
      #      say Dumper([ combine( [ @vals[$idx,$idx1] ], @vals[($idx1+1)..$lidx] )]);
      #      for my $idx2 ( ($idx1+1)..$nlidx ){
      #         say Dumper([ combine( [ @vals[$idx,$idx1,$idx2] ], @vals[($idx1+1)..$lidx] )]);
      #      }
      #   }
      #}
   }
   my %hval = map { join('--',@$_) => $_ } @rvals;
   return sort { scalar(@$a) <=> scalar(@$b) } sort { $a->[0] <=> $b->[0] } values %hval;

}
sub pDumper {
   my %h = (
     'ARRAY' => sub {
         my $r = '[ ';
         my @r = ();
         for my $e ( @_ ){
           push @r, pDumper( $e );
         }
         $r .= join(',',@r).' ]';
         return $r;
     },

   );
   my $r = '';
   for( @_ ){
      my $ref = ref($_);
      if( exists $h{ $ref } ){ 
        $r .= $h{ $ref }->(@$_);
      } else {
        $r .= $_;
      }
   }
   return $r;
}

sub gen_array {

   my $length = shift;
   my $l = $length - 1;
   my $s = scalar @_;
   my @a = ();
   my @n = 0 .. $l;
   if ( $s < $l ){
     for ( grep { $_ != $s } @n ){
       push @a, gen_array($length,@_,$_)
     }
   } else {
     
     for my $i ( 0 .. ($l-1) ){
       my @b = (@_,$i); 
       my $b = 0;
       my @c = map{ 
          $b[$b[$_]] == $_ 
       } @n ;
       $b += $_ for( @c );
       if( $b == $length ) {
         push @a, \@b;
       }
     }
   }
   return @a;

}

sub hex_number_str { '0x'.join('',reverse(@_)) };

sub rotate90 {
  my %r90_ = (
      4 => [3,0,1,2],
           #0,1,2,3,4,5,6,7
      8 => [2,3,7,6,1,0,4,5]
  );
  my $s = scalar @_;
  my @n = ();
  my @r90 = @{ $r90_{$s} };
  for my $i ( 0 .. ($s-1) ){
      my $ov = $_[ $i ]; # & 7;
      my $val = ( $ov & 8 ) ? 8 : $r90[$ov];
      $n[ $r90[$i] ] = $val ;
  }
  return @n;
}
sub same_rotate { grep { $_->{'index'} == $_->{'90i'} } @_ }
sub references {
    my %r =  map { $_->{reference} => 1 } @_;
    return sort{ $a <=> $b } keys %r;
}

sub rotations {
   my @ttiles = ( \@_ );
   for my $rt ( 1 .. 3 ){
        my $tiles = $ttiles[$rt-1];
        my @my_tiles = rotate90(@$tiles);
        $ttiles[$rt] = \@my_tiles;
   }
   return @ttiles;
}
sub tiles_hashes {
   my @ttiles = rotations( @_ );
   my @keys  = map { hex_number_str( @$_ ) } @ttiles; 
   my @ret = ();
   for my $i ( 0 .. 3 ) {
      push @ret, $keys[$i] => {
          raw => $ttiles[$i],
          name => $keys[$i],
          ref_name  => $keys[0],
          90   => $keys[(($i + 1) % 4)],
          180  => $keys[(($i + 2) % 4)],
          270  => $keys[(($i + 3) % 4)]
      };
   };
   @ret;
}
sub sorted_ref_keys {
    my %th = @_;
    sort {
       my $c = ($th{$a}->{ref_name} eq $th{$a}->{name});
       my $d = ($th{$b}->{ref_name} eq $th{$b}->{name});
       $d <=> $c
    } keys %th;
}
    
sub foo {
   my %h_t = ();
   my $ci = 1;
   my $cci = 36;

   for my $tile ( @_ ){
     
     next if exists $h_t{ hex_number_str(@$tile) }; # It's already built up, skip it.
     my $ref = $ci++;

     my @thash = tiles_hashes( @$tile );
     my %thash = @thash;
     my @keys = @thash[0,2,4,6];
     for my $i ( 0 .. 3 ){
        next if exists $h_t{$keys[$i]};
        $thash{$keys[$i]}->{index} = ( $thash{$keys[$i]}->{name} eq $thash{$keys[$i]}->{ref_name} )? $ref :$cci++;
        $thash{$keys[$i]}->{reference} = $ref;
        $h_t{$keys[$i]} = $thash{$keys[$i]};
     }

   }
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
   for my $key ( keys %h_t ){
      my $h = $h_t{$key};
      $h->{'90i'} = $h_t{ $h->{90} }->{index};
      $h->{'180i'} = $h_t{ $h->{180} }->{index};
      $h->{'270i'} = $h_t{ $h->{270} }->{index};
      $h->{'ref'}  = sprintf('0x'.'%02x'x4,$h->{'270i'},$h->{'180i'},$h->{'90i'},$h->{reference});
   }
   return ( $zero, sort { $a->{index} <=> $b->{index} } values %h_t );
}

sub c_code_array { 
   map { 
      my %h = %$_; 
      '{ '. join( ' , ',
            $h{name},
            map {
              (" " x (4 - length("$_")) ).$_ 
            } @h{qw( index 90i 180i 270i reference )}
          ) .
       ' } /* index:'.sprintf("%04i",$_->{index}).' */' } @_ 
}
#my $var_name = $ARGV[0] || die "Need a var name";
my $count = $ARGV[1] || 8;
my @f = gen_array($count);
use Data::Dumper;
my @tiles = foo(@f);
my @refs = references( @tiles );
my @ref_tiles_raws = map { $_->{raw} } @tiles[ @refs ];
my @combine = sort { scalar(@$a) <=> scalar(@$b) } prems( 0 .. 7 );

#say Dumper( \@ref_tiles_raws );

my %otiles = map { tiles_hashes( @$_ ) } map { 
     my @ret;
     my @pos = @$_;
     my @vals = map{8} 0 .. 7;
     map { 
        my $rt = [ @$_ ]; # make a copy
        my @rt = @$_;

        my %rpos = map { $_ => 1 } @pos, @rt[@pos];
        my @rpos = sort keys %rpos;
        @{$rt}[@rpos] = @vals;
        if( (scalar( grep { $_ == 8 } @$rt)%2) != 0 ) {
           say Dumper($rt, \@pos, $_, \%rpos, \@rpos,\@vals);
           die "Error!";

        }
        $rt;
     } @ref_tiles_raws[1..$#ref_tiles_raws];
} @combine;

my @otiles_count = sorted_ref_keys( %otiles );
{
   my $i = scalar( @tiles );
   $otiles{$_}->{index} = $i++ for ( @otiles_count );
   for my $k ( @otiles_count ) {
      my $h = $otiles{$k};
      $h->{'reference'} = $otiles{ $h->{ref_name} }->{index};
      $h->{'90i'} = $otiles{ $h->{90} }->{index};
      $h->{'180i'} = $otiles{ $h->{180} }->{index};
      $h->{'270i'} = $otiles{ $h->{270} }->{index};
      $h->{'ref'}  = sprintf('0x'.'%02x'x4,$h->{'270i'},$h->{'180i'},$h->{'90i'},$h->{reference});
   }
}

my $otiles_start = scalar @tiles;
my @otiles = values %otiles;
my @otiles_refs = references( @otiles );
@tiles = sort { $a->{index} <=> $b->{index} } @tiles, @otiles;
#say 'oTiles '.join (",\n", c_code_array(@otiles{ @otiles_count[ 0..5, 898..900 ] } ) );
#say 'Number of oTiles: ' . scalar @otiles_count;

#my @refs = references( same_rotate( @tiles ));
#say Dumper( \@refs, scalar @refs );
#my $last_id_tile = $refs[-1];
##  perl -E 'printf("0x%02x%02x%02x\n",155,7,105)'
say '#ifndef TILEMAP_HEADER_FILE';
say '#define TILEMAP_HEADER_FILE';
say "/* Generated using: $0 ".join( ' ',@ARGV)." */";
say 'const int num_id_tiles = '.scalar @refs.';';
say 'const int *id_tiles = { '.join(' , ',@refs).' };';
say 'const int osais_tiles_start = '.$otiles_start.';';
say 'const int osais_num_id_tiles = '.scalar @otiles_refs.';';
say 'const int *osais_id_tiles = { '.join(' , ',@otiles_refs).' };';
say 'const int num_tiles = '.scalar @tiles.';';
say <<C_CODE;
enum map_tile_indexs {
   tile_ref     = 0,
   tile_index   = 1,
   tile_idx_90  = 2,
   tile_idx_180 = 3,
   tile_idx_270 = 4,
   tile_idx_ref = 5
};
C_CODE

say 'const tile_map_type map_tiles[' . (scalar @tiles) . '][6] = {';
say '/*  DDLLRRUU , index, 90 index, 180 index, 270 index , reference index */';
say join( ",\n", c_code_array(@tiles) );
say '};';
say;
#say 'const int num_osias_tiles = '.scalar @otiles.';';
#say 'const tile_maps_type osias_tiles[][] = {';
#say '/*  DDLLRRUU , reference index, 90 index, 180 index, 270 index */';
#say join( ",\n", c_code_array(@otiles) );
#say '};';
say;
say '#endif';



#
#say;
#say join( ",\n", map { hex_number_str( @$_ ) } @f); 
#say join( ",\n", map { hex_number_str(@$_) =>  hex_number_str( rotate90(@$_) ) } @f); 
#
