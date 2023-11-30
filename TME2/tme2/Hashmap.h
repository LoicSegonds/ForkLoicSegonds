#pragma once
#include <forward_list>
#include <vector>

namespace par{
  template<typename K, typename V>
  class Hashtable{
  public:
    class Entry{
    public:
      const K key;
      V value;
      Entry(const K key, const V value):key(key),value(value){}

      operator std::pair<K, V>() const {
        return std::make_pair(key, value);
      }
    };
  private:
    typedef std::vector<std::forward_list<Entry>> buckets_t;
    buckets_t buckets;
    size_t sz;

  public:
    Hashtable(size_t siz):buckets(siz),sz(0){}

    V * get(const K & key){
      size_t h = std::hash<K>()(key);
      size_t target = h%buckets.size();
      for(Entry & e : buckets[target]){
        if(e.key==key)
        return &e.value;
      }
      return nullptr;
    }

    bool put(const K & key, const V & val){
      size_t h= std::hash<K>()(key);
      size_t target = h%buckets.size();
      for(Entry & e : buckets[target]){
        if(e.key==key){
          e.value=val;
          return true;
        }
      }
      ++sz;
      buckets[target].emplace_front(key,val);
      return false;
    }

    size_t size() const{
      return sz;
    }

    class iterator{

      buckets_t &buckets;
      typename buckets_t::iterator vit;
      typename std::forward_list<Entry>::iterator lit;

    public:

      iterator(buckets_t &b):buckets(b){
        if (!b.empty()){
          vit=buckets.begin();
          if(vit != buckets.end() && !(vit->empty()))
            lit=vit->begin();
          else
            lit=typename std::forward_list<Entry>::iterator();
        } else {
            vit=typename buckets_t::iterator();
            lit=typename std::forward_list<Entry>::iterator();
        }
      }

      //incrément
       iterator &operator++(){
           ++lit;
           if(lit==vit->end()){
             if(++vit!=buckets.end()){
               lit=vit->begin();
             }else{
               vit=typename buckets_t::iterator();
               lit=typename std::forward_list<Entry>::iterator();
             }
           }
           return *this;
       }

       //comparaison d'inégalité
        bool operator!=(const iterator &other){
            return (vit!=other.vit)||(lit!=other.lit);
        }

        //déréférencement
        Entry &operator*() {
            return *lit;
        }
    };
    //début de la table
    iterator begin(){
      return iterator(buckets);
    }

    //fin de la table
    iterator end(){
      buckets_t a=buckets_t();
      return iterator(a);
    }


    //Q1 et Q2 TME 3
    size_t count(iterator begin,iterator end){
    	size_t count=0;
    	for(iterator a=begin;a<end;a++){
    		++count;
    	}
    	return count;
    }

    size_t count_if_equal (iterator begin, iterator end, const V & val){
    	size_t count=0;
    	for(iterator a=begin;a<end;a++){
    		if(*a==val)
    			++count;
    	}
    	return count;
    }


  };

}
