#pragma once
#include<iostream>
#include<vector>
#include<algorithm>

namespace Querying{
    class Query{
        public:
        virtual bool check(int value) const = 0;
        virtual ~Query(){};
        virtual Query* clone() const=0;
    };
    class CompositeQuery{
        private:
        int size;
        std::vector<Query*> queries;
        public:
        void addQuery(Query* query){
            queries.push_back(query);
        }
        CompositeQuery(int n =5 ): size(n){
            queries.reserve(n);
        }
        bool matches(int val)const {
            bool f=true;
            for(auto q: queries){
                if(!( q->check(val))){
                    f=false;
                }
            }
            return f;
        }
        ~CompositeQuery();
        //constructor copy
        CompositeQuery(const CompositeQuery& other);
     
        CompositeQuery& operator=(const CompositeQuery& other);
    };
    namespace Simple{
        class GreaterThan : public Query{
            private :
            int value;
            public:
            GreaterThan(int val): value(val){}

            bool check(int val) const override{
                return value < val;
            }
            Query* clone()const override{
                return new GreaterThan(*this);
            }
        };
        class LessThan: public Query{
                private:
                int value;
                public:
                LessThan(int val): value(val){}
                bool check(int val)const override{
                    return  value > val;
                }
                Query* clone() const override{
                    return new LessThan(*this);
                }
        };
        class IsEven: public Query{
            public:
            
            bool check(int val)const override{
                    return val%2==0;
                }
            Query* clone() const override{
                return new IsEven(*this);
            }
        };
        class EqualTo: public Query{
            private:
            int value;
            public:
            EqualTo(int val) : value(val) {} 
            bool check(int val) const override{
                return val==value;
            }
            Query* clone() const override{
                return new EqualTo(*this);
            }
        };
        class NotQuery: public Query{
            private:
            
            Query* brakeQuery;
            public:
            NotQuery(Query* b): brakeQuery(b){}

            bool check(int val) const override{
                return !(brakeQuery->check(val));
            }
            Query* clone() const override{
                return new NotQuery(*this);
            }
            ~NotQuery(){ 
                delete brakeQuery;
            }


        };

    }
    std::vector<int> filter(const std::vector<int>& data, const CompositeQuery& queries);
    
}