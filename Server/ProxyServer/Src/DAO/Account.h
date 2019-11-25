#pragma once

#include <Entity/Account.h>
#include <DAO/DAO.h>
#include <System/Log.h>

namespace Swtor{
	namespace DAO
	{
		template <>
		inline void DAO<Entity::Account>::Load(SimpleDB::Database& pDatabase)
		{
			try
			{
				std::ostringstream oss;
				oss << "SELECT swtor_user.id, users.user_username, users.user_level FROM swtor_user"
					<< " LEFT JOIN users ON swtor_user.id=users.id"
					<< " WHERE session_id='" 
					<< pDatabase.escapeString(mEntity.SessionId)<< "';";
					
				SimpleDB::Query query(pDatabase);
				SimpleDB::StringColumn user(61);
				SimpleDB::IntColumn id,level;
				SimpleDB::Column * cols[] = {&id,&user,&level};
				query.bind(cols,3);
				query.execute(oss.str());

				if(query.fetchRow())
				{
					mEntity.User = user.value();
					mEntity.Level = level.value();
					mEntity.Id = id.value();
				}
				else
					throw std::runtime_error("Account not found");

				std::ostringstream os;
				os << "UPDATE `swtor_user` SET `server_id` ='"
					<< pDatabase.escapeString(mEntity.ServerId)
					<< "' WHERE `session_id` ='"
					<< pDatabase.escapeString(mEntity.SessionId)<< "';";

				//System::Log::GetInstance()->Debug(os.str());
				pDatabase.voidQuery(os.str());

				OnEvent(IDAO::LOAD, true);
			}
			catch(std::exception& e)
			{
				System::Log::GetInstance()->Error(e.what());
				OnEvent(IDAO::LOAD, false);
			}			
		}

		template <>
		inline void DAO<Entity::Account>::Save(SimpleDB::Database& pDatabase)
		{
			try
			{
				/*std::ostringstream oss;
				oss << "UPDATE realm_accounts SET ticket='" << mEntity._ticket << "' WHERE guid='" << mEntity._id << "'";
				pDatabase.voidQuery(oss.str());*/
			}
			catch(std::exception& e)
			{
				Swtor::System::Log::GetInstance()->Error(e.what());
			}

			OnEvent(IDAO::SAVE, false);
		}
	}
}